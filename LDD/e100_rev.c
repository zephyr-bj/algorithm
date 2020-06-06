/*
 * e100_probe calling 
 *     netif_napi_add(netdev, &nic->napi, e100_poll, E100_NAPI_WEIGHT);
 * static int e100_poll(struct napi_struct *napi, int budget) calling
 *     e100_rx_clean(nic, &work_done, budget);
 * static void e100_rx_clean(struct nic *nic, unsigned int *work_done, unsigned int work_to_do) calling
 *     e100_rx_indicate(nic, rx, work_done, work_to_do);
 * static int e100_rx_indicate(struct nic *nic, struct rx *rx, unsigned int *work_done, unsigned int work_to_do) calling
 *     netif_receive_skb(skb);
 *     
 * static int e100_up(struct nic *nic) calling
 *     request_irq(nic->pdev->irq, e100_intr, IRQF_SHARED, nic->netdev->name, nic->netdev)
 * static irqreturn_t e100_intr(int irq, void *dev_id) calling
 *     if (likely(napi_schedule_prep(&nic->napi))) {
 *         e100_disable_irq(nic);
 *         __napi_schedule(&nic->napi);
 *     }
 * 
 * static int e100_up(struct nic *nic) calling
 *     e100_rx_alloc_list(nic)    
 * static int e100_rx_alloc_list(struct nic *nic) calling
 *     e100_rx_alloc_skb(nic, rx)
 * static int e100_rx_alloc_skb(struct nic *nic, struct rx *rx) calling
 *     netdev_alloc_skb_ip_align(nic->netdev, RFD_BUF_LEN)
 */
 
#define ALIGN(x,a) (((x)+(a)-1)&~((a)-1))
 
#include <include/linux/unaligned/le_byteshift.h>
static inline void __put_unaligned_le16(u16 val, u8 *p)
{
    *p++ = val;
    *p++ = val >> 8;
}
static inline void __put_unaligned_le32(u32 val, u8 *p)
{
    __put_unaligned_le16(val >> 16, p + 2);
    __put_unaligned_le16(val, p);
}
static inline void __put_unaligned_le64(u64 val, u8 *p)
{
    __put_unaligned_le32(val >> 32, p + 4);
    __put_unaligned_le32(val, p);
}   
      

static inline void e100_start_receiver(struct nic *nic, struct rx *rx)
{
    if (!nic->rxs) return;
    if (RU_SUSPENDED != nic->ru_running) return;

    /* handle init time starts */
    if (!rx) rx = nic->rxs;

    /* (Re)start RU if suspended or idle and RFA is non-NULL */
    if (rx->skb) {
        e100_exec_cmd(nic, ruc_start, rx->dma_addr);
        nic->ru_running = RU_RUNNING;
    }
}

static int e100_up(struct nic *nic)
{
    ...
    e100_start_receiver(nic, NULL);
    ...
}

static int e100_rx_indicate(struct nic *nic, struct rx *rx,
    unsigned int *work_done, unsigned int work_to_do)
{
    struct net_device *dev = nic->netdev;
    struct sk_buff *skb = rx->skb;
    struct rfd *rfd = (struct rfd *)skb->data;
    u16 rfd_status, actual_size;
    u16 fcs_pad = 0;

    if (unlikely(work_done && *work_done >= work_to_do))
        return -EAGAIN;

    /* Need to sync before taking a peek at cb_complete bit */
    pci_dma_sync_single_for_cpu(nic->pdev, rx->dma_addr,
        sizeof(struct rfd), PCI_DMA_BIDIRECTIONAL);
    rfd_status = le16_to_cpu(rfd->status);

    netif_printk(nic, rx_status, KERN_DEBUG, nic->netdev,
             "status=0x%04X\n", rfd_status);
    dma_rmb(); /* read size after status bit */

    /* If data isn't ready, nothing to indicate */
    if (unlikely(!(rfd_status & cb_complete))) {
        /* If the next buffer has the el bit, but we think the receiver
         * is still running, check to see if it really stopped while
         * we had interrupts off.
         * This allows for a fast restart without re-enabling
         * interrupts */
        if ((le16_to_cpu(rfd->command) & cb_el) &&
            (RU_RUNNING == nic->ru_running))

            if (ioread8(&nic->csr->scb.status) & rus_no_res)
                nic->ru_running = RU_SUSPENDED;
        pci_dma_sync_single_for_device(nic->pdev, rx->dma_addr,
                           sizeof(struct rfd),
                           PCI_DMA_FROMDEVICE);
        return -ENODATA;
    }

    /* Get actual data size */
    if (unlikely(dev->features & NETIF_F_RXFCS))
        fcs_pad = 4;
    actual_size = le16_to_cpu(rfd->actual_size) & 0x3FFF;
    if (unlikely(actual_size > RFD_BUF_LEN - sizeof(struct rfd)))
        actual_size = RFD_BUF_LEN - sizeof(struct rfd);

    /* Get data */
    pci_unmap_single(nic->pdev, rx->dma_addr,
        RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);

    /* If this buffer has the el bit, but we think the receiver
     * is still running, check to see if it really stopped while
     * we had interrupts off.
     * This allows for a fast restart without re-enabling interrupts.
     * This can happen when the RU sees the size change but also sees
     * the el bit set. */
    if ((le16_to_cpu(rfd->command) & cb_el) &&
        (RU_RUNNING == nic->ru_running)) {

        if (ioread8(&nic->csr->scb.status) & rus_no_res)
        nic->ru_running = RU_SUSPENDED;
    }

    /* Pull off the RFD and put the actual data (minus eth hdr) */
    skb_reserve(skb, sizeof(struct rfd));
    skb_put(skb, actual_size);
    skb->protocol = eth_type_trans(skb, nic->netdev);

    /* If we are receiving all frames, then don't bother
     * checking for errors.
     */
    if (unlikely(dev->features & NETIF_F_RXALL)) {
        if (actual_size > ETH_DATA_LEN + VLAN_ETH_HLEN + fcs_pad)
            /* Received oversized frame, but keep it. */
            nic->rx_over_length_errors++;
        goto process_skb;
    }

    if (unlikely(!(rfd_status & cb_ok))) {
        /* Don't indicate if hardware indicates errors */
        dev_kfree_skb_any(skb);
        dev_kfree_skb_any(skb);
    } else if (actual_size > ETH_DATA_LEN + VLAN_ETH_HLEN + fcs_pad) {
        /* Don't indicate oversized frames */
        nic->rx_over_length_errors++;
        dev_kfree_skb_any(skb);
    } else {
process_skb:
        dev->stats.rx_packets++;
        dev->stats.rx_bytes += (actual_size - fcs_pad);
        netif_receive_skb(skb);
        if (work_done)
            (*work_done)++;
    }

    rx->skb = NULL;

    return 0;
}


static void e100_rx_clean(struct nic *nic, unsigned int *work_done,
    unsigned int work_to_do)
{
    struct rx *rx;
    int restart_required = 0, err = 0;
    struct rx *old_before_last_rx, *new_before_last_rx;
    struct rfd *old_before_last_rfd, *new_before_last_rfd;

    /* Indicate newly arrived packets */
    for (rx = nic->rx_to_clean; rx->skb; rx = nic->rx_to_clean = rx->next) {
        err = e100_rx_indicate(nic, rx, work_done, work_to_do);
        /* Hit quota or no more to clean */
        if (-EAGAIN == err || -ENODATA == err)
            break;
    }


    /* On EAGAIN, hit quota so have more work to do, restart once
     * cleanup is complete.
     * Else, are we already rnr? then pay attention!!! this ensures that
     * the state machine progression never allows a start with a
     * partially cleaned list, avoiding a race between hardware
     * and rx_to_clean when in NAPI mode */
    if (-EAGAIN != err && RU_SUSPENDED == nic->ru_running)
        restart_required = 1;

    old_before_last_rx = nic->rx_to_use->prev->prev;
    old_before_last_rfd = (struct rfd *)old_before_last_rx->skb->data;

    /* Alloc new skbs to refill list */
    for (rx = nic->rx_to_use; !rx->skb; rx = nic->rx_to_use = rx->next) {
        if (unlikely(e100_rx_alloc_skb(nic, rx)))
            break; /* Better luck next time (see watchdog) */
    }

    new_before_last_rx = nic->rx_to_use->prev->prev;
    if (new_before_last_rx != old_before_last_rx) {
        /* Set the el-bit on the buffer that is before the last buffer.
         * This lets us update the next pointer on the last buffer
         * without worrying about hardware touching it.
         * We set the size to 0 to prevent hardware from touching this
         * buffer.
         * When the hardware hits the before last buffer with el-bit
         * and size of 0, it will RNR interrupt, the RUS will go into
         * the No Resources state.  It will not complete nor write to
         * this buffer. */
        new_before_last_rfd =
            (struct rfd *)new_before_last_rx->skb->data;
        new_before_last_rfd->size = 0;
        new_before_last_rfd->command |= cpu_to_le16(cb_el);
        pci_dma_sync_single_for_device(nic->pdev,
            new_before_last_rx->dma_addr, sizeof(struct rfd),
            PCI_DMA_BIDIRECTIONAL);

        /* Now that we have a new stopping point, we can clear the old
         * stopping point.  We must sync twice to get the proper
         * ordering on the hardware side of things. */
        old_before_last_rfd->command &= ~cpu_to_le16(cb_el);
        pci_dma_sync_single_for_device(nic->pdev,
            old_before_last_rx->dma_addr, sizeof(struct rfd),
            PCI_DMA_BIDIRECTIONAL);
        old_before_last_rfd->size = cpu_to_le16(VLAN_ETH_FRAME_LEN
                            + ETH_FCS_LEN);
        pci_dma_sync_single_for_device(nic->pdev,
            old_before_last_rx->dma_addr, sizeof(struct rfd),
            PCI_DMA_BIDIRECTIONAL);
    }

    if (restart_required) {
        // ack the rnr?
        iowrite8(stat_ack_rnr, &nic->csr->scb.stat_ack);
        e100_start_receiver(nic, nic->rx_to_clean);
        if (work_done)
            (*work_done)++;
    }
}


static int e100_poll(struct napi_struct *napi, int budget)
{
    struct nic *nic = container_of(napi, struct nic, napi);
    unsigned int work_done = 0;

    e100_rx_clean(nic, &work_done, budget);
    e100_tx_clean(nic);

    /* If budget not fully consumed, exit the polling mode */
    if (work_done < budget) {
        napi_complete(napi);
        e100_enable_irq(nic);
    }

    return work_done;
}

#define RFD_BUF_LEN (sizeof(struct rfd) + VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)
static int e100_rx_alloc_skb(struct nic *nic, struct rx *rx)
{
    if (!(rx->skb = netdev_alloc_skb_ip_align(nic->netdev, RFD_BUF_LEN)))
        return -ENOMEM;
    
    /* Init, and map the RFD. */
    skb_copy_to_linear_data(rx->skb, &nic->blank_rfd, sizeof(struct rfd));
    rx->dma_addr = pci_map_single(nic->pdev, rx->skb->data,
        RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);

    if (pci_dma_mapping_error(nic->pdev, rx->dma_addr)) {
        dev_kfree_skb_any(rx->skb);
        rx->skb = NULL;
        rx->dma_addr = 0;
        return -ENOMEM;
    }
    
    /* Link the RFD to end of RFA by linking previous RFD to
     * this one.  We are safe to touch the previous RFD because
     * it is protected by the before last buffer's el bit being set */
    if (rx->prev->skb) {
        struct rfd *prev_rfd = (struct rfd *)rx->prev->skb->data;
        put_unaligned_le32(rx->dma_addr, &prev_rfd->link);
        pci_dma_sync_single_for_device(nic->pdev, rx->prev->dma_addr,
            sizeof(struct rfd), PCI_DMA_BIDIRECTIONAL);
    }

    return 0;
}
 
static void e100_rx_clean_list(struct nic *nic)
{
    struct rx *rx;
    unsigned int i, count = nic->params.rfds.count;

    nic->ru_running = RU_UNINITIALIZED;

    if (nic->rxs) {
        for (rx = nic->rxs, i = 0; i < count; rx++, i++) {
            if (rx->skb) {
                pci_unmap_single(nic->pdev, rx->dma_addr,
                    RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);
                dev_kfree_skb(rx->skb);
            }
        }
        kfree(nic->rxs);
        nic->rxs = NULL;
    }

    nic->rx_to_use = nic->rx_to_clean = NULL;
}
static int e100_rx_alloc_list(struct nic *nic)
{
    struct rx *rx;
    unsigned int i, count = nic->params.rfds.count;
    struct rfd *before_last;

    nic->rx_to_use = nic->rx_to_clean = NULL;
    nic->ru_running = RU_UNINITIALIZED;

    if (!(nic->rxs = kcalloc(count, sizeof(struct rx), GFP_ATOMIC)))
        return -ENOMEM;

    for (rx = nic->rxs, i = 0; i < count; rx++, i++) {
        rx->next = (i + 1 < count) ? rx + 1 : nic->rxs;
        rx->prev = (i == 0) ? nic->rxs + count - 1 : rx - 1;
        if (e100_rx_alloc_skb(nic, rx)) {
            e100_rx_clean_list(nic);
            return -ENOMEM;
        }
    }
    /* Set the el-bit on the buffer that is before the last buffer.
     * This lets us update the next pointer on the last buffer without
     * worrying about hardware touching it.
     * We set the size to 0 to prevent hardware from touching this buffer.
     * When the hardware hits the before last buffer with el-bit and size
     * of 0, it will RNR interrupt, the RU will go into the No Resources
     * state.  It will not complete nor write to this buffer. */
    rx = nic->rxs->prev->prev;
    before_last = (struct rfd *)rx->skb->data;
    before_last->command |= cpu_to_le16(cb_el);
    before_last->size = 0;
    pci_dma_sync_single_for_device(nic->pdev, rx->dma_addr,
        sizeof(struct rfd), PCI_DMA_BIDIRECTIONAL);

    nic->rx_to_use = nic->rx_to_clean = nic->rxs;
    nic->ru_running = RU_SUSPENDED;

    return 0;
}

 
static irqreturn_t e100_intr(int irq, void *dev_id)
{                          
    struct net_device *netdev = dev_id;
    struct nic *nic = netdev_priv(netdev);
    u8 stat_ack = ioread8(&nic->csr->scb.stat_ack);
    
    netif_printk(nic, intr, KERN_DEBUG, nic->netdev,
             "stat_ack = 0x%02X\n", stat_ack);

    if (stat_ack == stat_ack_not_ours ||    /* Not our interrupt */
       stat_ack == stat_ack_not_present)    /* Hardware is ejected */
        return IRQ_NONE;

    /* Ack interrupt(s) */
    iowrite8(stat_ack, &nic->csr->scb.stat_ack);

    /* We hit Receive No Resource (RNR); restart RU after cleaning */
    if (stat_ack & stat_ack_rnr)
        nic->ru_running = RU_SUSPENDED;
    
    if (likely(napi_schedule_prep(&nic->napi))) {
        e100_disable_irq(nic);
        __napi_schedule(&nic->napi);
    }

    return IRQ_HANDLED;
}   


