/* "e100_exec_cmd" interface with the hardware register
 * "e100_exec_cb" implement the cb_to_send, until it reaches cb_to_use, using e100_exec_cmd
 * * in case any error happens, call "e100_tx_timeout_task*
 * * otherwise, construct the cb by a function pointed by "cb_prepare" 
 * such cb_prepare functions include:
 * * "e100_xmit_prepare"
 * * "e100_configure"
 * * "e100_setup_ucode"
 * * "e100_setup_iaaddr"
 * * "e100_dump"
 * * "e100_multi"
 */
 
/* "e100_alloc_cbs" allocate dma coherent kernel memory by "pci_pool_alloc"
 * "e100_clean_cbs" unmap and free the tx frame buffer for TX DMA, 
 * * free the cb by "pci_pool_free"
 * "e100_tx_clean" clean CBs marked complete
 */

static void e100_clean_cbs(struct nic *nic)
{
    if (nic->cbs) {
        while (nic->cbs_avail != nic->params.cbs.count) {
            struct cb *cb = nic->cb_to_clean;
            if (cb->skb) {
                pci_unmap_single(nic->pdev,
                    le32_to_cpu(cb->u.tcb.tbd.buf_addr),
                    le16_to_cpu(cb->u.tcb.tbd.size),
                    PCI_DMA_TODEVICE);
                dev_kfree_skb(cb->skb);
            }
            nic->cb_to_clean = nic->cb_to_clean->next;
            nic->cbs_avail++;
        }
        pci_pool_free(nic->cbs_pool, nic->cbs, nic->cbs_dma_addr);
        nic->cbs = NULL; 
        nic->cbs_avail = 0;
    }
    nic->cuc_cmd = cuc_start;
    nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean =
        nic->cbs;
}

static int e100_alloc_cbs(struct nic *nic)
{
    struct cb *cb;
    unsigned int i, count = nic->params.cbs.count;

    nic->cuc_cmd = cuc_start;
    nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean = NULL;
    nic->cbs_avail = 0;

    nic->cbs = pci_pool_alloc(nic->cbs_pool, GFP_KERNEL,
                  &nic->cbs_dma_addr);
    if (!nic->cbs)
        return -ENOMEM;
    memset(nic->cbs, 0, count * sizeof(struct cb));

    for (cb = nic->cbs, i = 0; i < count; cb++, i++) {
        cb->next = (i + 1 < count) ? cb + 1 : nic->cbs;
        cb->prev = (i == 0) ? nic->cbs + count - 1 : cb - 1;

        cb->dma_addr = nic->cbs_dma_addr + i * sizeof(struct cb);
        cb->link = cpu_to_le32(nic->cbs_dma_addr +
            ((i+1) % count) * sizeof(struct cb));
    }

    nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean = nic->cbs;
    nic->cbs_avail = count;

    return 0;
}

static int e100_tx_clean(struct nic *nic)
{
    struct net_device *dev = nic->netdev;
    struct cb *cb;
    int tx_cleaned = 0;

    spin_lock(&nic->cb_lock);

    /* Clean CBs marked complete */
    for (cb = nic->cb_to_clean;
        cb->status & cpu_to_le16(cb_complete);
        cb = nic->cb_to_clean = cb->next) {
        dma_rmb(); /* read skb after status */
        netif_printk(nic, tx_done, KERN_DEBUG, nic->netdev,
                 "cb[%d]->status = 0x%04X\n",
                 (int)(((void*)cb - (void*)nic->cbs)/sizeof(struct cb)),
                 cb->status);

        if (likely(cb->skb != NULL)) {
            dev->stats.tx_packets++;
            dev->stats.tx_bytes += cb->skb->len;

            pci_unmap_single(nic->pdev,
                le32_to_cpu(cb->u.tcb.tbd.buf_addr),
                le16_to_cpu(cb->u.tcb.tbd.size),
                PCI_DMA_TODEVICE);
            dev_kfree_skb_any(cb->skb);
            cb->skb = NULL;
            tx_cleaned = 1;
        }
        cb->status = 0;
        nic->cbs_avail++;
    }

    spin_unlock(&nic->cb_lock);

    /* Recover from running out of Tx resources in xmit_frame */
    if (unlikely(tx_cleaned && netif_queue_stopped(nic->netdev)))
        netif_wake_queue(nic->netdev);

    return tx_cleaned;
}


#define E100_WAIT_SCB_TIMEOUT 20000 /* we might have to wait 100ms!!! */
#define E100_WAIT_SCB_FAST 20       /* delay like the old code */
static int e100_exec_cmd(struct nic *nic, u8 cmd, dma_addr_t dma_addr)
{
    unsigned long flags;
    unsigned int i;
    int err = 0;

    spin_lock_irqsave(&nic->cmd_lock, flags);

    /* Previous command is accepted when SCB clears */
    for (i = 0; i < E100_WAIT_SCB_TIMEOUT; i++) {
        if (likely(!ioread8(&nic->csr->scb.cmd_lo)))
            break;
        cpu_relax();
        if (unlikely(i > E100_WAIT_SCB_FAST))
            udelay(5);
    }
    if (unlikely(i == E100_WAIT_SCB_TIMEOUT)) {
        err = -EAGAIN;
        goto err_unlock;
    }

    if (unlikely(cmd != cuc_resume))
        iowrite32(dma_addr, &nic->csr->scb.gen_ptr);
    iowrite8(cmd, &nic->csr->scb.cmd_lo);

err_unlock:
    spin_unlock_irqrestore(&nic->cmd_lock, flags);

    return err;
}

static int e100_exec_cb(struct nic *nic, struct sk_buff *skb,
    int (*cb_prepare)(struct nic *, struct cb *, struct sk_buff *))
{
    struct cb *cb;
    unsigned long flags;
    int err;

    spin_lock_irqsave(&nic->cb_lock, flags);

    if (unlikely(!nic->cbs_avail)) {
        err = -ENOMEM;
        goto err_unlock;
    }

    cb = nic->cb_to_use;
    nic->cb_to_use = cb->next;
    nic->cbs_avail--;
    cb->skb = skb;

    err = cb_prepare(nic, cb, skb);
    if (err)
        goto err_unlock;

    if (unlikely(!nic->cbs_avail))
        err = -ENOSPC;


    /* Order is important otherwise we'll be in a race with h/w:
     * set S-bit in current first, then clear S-bit in previous. */
    cb->command |= cpu_to_le16(cb_s);
    dma_wmb();
    cb->prev->command &= cpu_to_le16(~cb_s);

    while (nic->cb_to_send != nic->cb_to_use) {
        if (unlikely(e100_exec_cmd(nic, nic->cuc_cmd,
            nic->cb_to_send->dma_addr))) {
            /* Ok, here's where things get sticky.  It's
             * possible that we can't schedule the command
             * because the controller is too busy, so
             * let's just queue the command and try again
             * when another command is scheduled. */
            if (err == -ENOSPC) {
                //request a reset
                schedule_work(&nic->tx_timeout_task);
            }
            break;
        } else {
            nic->cuc_cmd = cuc_resume;
            nic->cb_to_send = nic->cb_to_send->next;
        }
    }

err_unlock:
    spin_unlock_irqrestore(&nic->cb_lock, flags);

    return err;
}

static void e100_tx_timeout_task(struct work_struct *work)
{
    struct nic *nic = container_of(work, struct nic, tx_timeout_task);
    struct net_device *netdev = nic->netdev;

    netif_printk(nic, tx_err, KERN_DEBUG, nic->netdev,
             "scb.status=0x%02X\n", ioread8(&nic->csr->scb.status));

    rtnl_lock();
    if (netif_running(netdev)) {
        e100_down(netdev_priv(netdev));
        e100_up(netdev_priv(netdev));
    }
    rtnl_unlock();
}

static int e100_xmit_prepare(struct nic *nic, struct cb *cb,
    struct sk_buff *skb)
{
    dma_addr_t dma_addr;
    cb->command = nic->tx_command;

    dma_addr = pci_map_single(nic->pdev,
                  skb->data, skb->len, PCI_DMA_TODEVICE);
    /* If we can't map the skb, have the upper layer try later */
    if (pci_dma_mapping_error(nic->pdev, dma_addr)) {
        dev_kfree_skb_any(skb);
        skb = NULL;
        return -ENOMEM;
    }

    /*
     * Use the last 4 bytes of the SKB payload packet as the CRC, used for
     * testing, ie sending frames with bad CRC.
     */
    if (unlikely(skb->no_fcs))
        cb->command |= cpu_to_le16(cb_tx_nc);
    else
        cb->command &= ~cpu_to_le16(cb_tx_nc);

    /* interrupt every 16 packets regardless of delay */
    if ((nic->cbs_avail & ~15) == nic->cbs_avail)
        cb->command |= cpu_to_le16(cb_i);
    cb->u.tcb.tbd_array = cb->dma_addr + offsetof(struct cb, u.tcb.tbd);
    cb->u.tcb.tcb_byte_count = 0;
    cb->u.tcb.threshold = nic->tx_threshold;
    cb->u.tcb.tbd_count = 1;
    cb->u.tcb.tbd.buf_addr = cpu_to_le32(dma_addr);
    cb->u.tcb.tbd.size = cpu_to_le16(skb->len);
    skb_tx_timestamp(skb);
    return 0;
}

static int e100_configure(struct nic *nic, struct cb *cb, struct sk_buff *skb)
{
    struct config *config = &cb->u.config;
    u8 *c = (u8 *)config;
    struct net_device *netdev = nic->netdev;

    cb->command = cpu_to_le16(cb_config);

    memset(config, 0, sizeof(struct config));

    config->byte_count = 0x16;      /* bytes in this struct */
    config->rx_fifo_limit = 0x8;        /* bytes in FIFO before DMA */
    config->direct_rx_dma = 0x1;        /* reserved */
    config->standard_tcb = 0x1;     /* 1=standard, 0=extended */
    config->standard_stat_counter = 0x1;    /* 1=standard, 0=extended */
    config->rx_discard_short_frames = 0x1;  /* 1=discard, 0=pass */
    config->tx_underrun_retry = 0x3;    /* # of underrun retries */
    if (e100_phy_supports_mii(nic))
        config->mii_mode = 1;           /* 1=MII mode, 0=i82503 mode */
    config->pad10 = 0x6;
    config->no_source_addr_insertion = 0x1; /* 1=no, 0=yes */
    config->preamble_length = 0x2;      /* 0=1, 1=3, 2=7, 3=15 bytes */
    config->ifs = 0x6;          /* x16 = inter frame spacing */
    config->ip_addr_hi = 0xF2;      /* ARP IP filter - not used */
    config->pad15_1 = 0x1;
    config->pad15_2 = 0x1;
    config->crs_or_cdt = 0x0;       /* 0=CRS only, 1=CRS or CDT */
    config->fc_delay_hi = 0x40;     /* time delay for fc frame */
    config->tx_padding = 0x1;       /* 1=pad short frames */
    config->fc_priority_threshold = 0x7;    /* 7=priority fc disabled */
    config->pad18 = 0x1;
    config->full_duplex_pin = 0x1;      /* 1=examine FDX# pin */
    config->pad20_1 = 0x1F;
    config->fc_priority_location = 0x1; /* 1=byte#31, 0=byte#19 */
    config->pad21_1 = 0x5;

    config->adaptive_ifs = nic->adaptive_ifs;
    config->loopback = nic->loopback;

    if (nic->mii.force_media && nic->mii.full_duplex)
        config->full_duplex_force = 0x1;    /* 1=force, 0=auto */

    if (nic->flags & promiscuous || nic->loopback) {
        config->rx_save_bad_frames = 0x1;   /* 1=save, 0=discard */
        config->rx_discard_short_frames = 0x0;  /* 1=discard, 0=save */
        config->promiscuous_mode = 0x1;     /* 1=on, 0=off */
    }

    if (unlikely(netdev->features & NETIF_F_RXFCS))
        config->rx_crc_transfer = 0x1;  /* 1=save, 0=discard */

    if (nic->flags & multicast_all)
        config->multicast_all = 0x1;        /* 1=accept, 0=no */

    /* disable WoL when up */
    if (netif_running(nic->netdev) || !(nic->flags & wol_magic))
        config->magic_packet_disable = 0x1; /* 1=off, 0=on */

    if (nic->mac >= mac_82558_D101_A4) {
        config->fc_disable = 0x1;   /* 1=Tx fc off, 0=Tx fc on */
        config->mwi_enable = 0x1;   /* 1=enable, 0=disable */
        config->standard_tcb = 0x0; /* 1=standard, 0=extended */
        config->rx_long_ok = 0x1;   /* 1=VLANs ok, 0=standard */
        if (nic->mac >= mac_82559_D101M) {
            config->tno_intr = 0x1;     /* TCO stats enable */
            /* Enable TCO in extended config */
            if (nic->mac >= mac_82551_10) {
                config->byte_count = 0x20; /* extended bytes */
                config->rx_d102_mode = 0x1; /* GMRC for TCO */
            }
        } else {
            config->standard_stat_counter = 0x0;
        }
    }

    if (netdev->features & NETIF_F_RXALL) {
        config->rx_save_overruns = 0x1; /* 1=save, 0=discard */
        config->rx_save_bad_frames = 0x1;       /* 1=save, 0=discard */
        config->rx_discard_short_frames = 0x0;  /* 1=discard, 0=save */
    }

    netif_printk(nic, hw, KERN_DEBUG, nic->netdev, "[00-07]=%8ph\n",
             c + 0);
    netif_printk(nic, hw, KERN_DEBUG, nic->netdev, "[08-15]=%8ph\n",
             c + 8);
    netif_printk(nic, hw, KERN_DEBUG, nic->netdev, "[16-23]=%8ph\n",
             c + 16);
    return 0;
}

static int e100_setup_ucode(struct nic *nic, struct cb *cb,
                 struct sk_buff *skb)
{
    const struct firmware *fw = (void *)skb;
    u8 timer, bundle, min_size;

    /* It's not a real skb; we just abused the fact that e100_exec_cb
       will pass it through to here... */
    cb->skb = NULL;

    /* firmware is stored as little endian already */
    memcpy(cb->u.ucode, fw->data, UCODE_SIZE * 4);

    /* Read timer, bundle and min_size from end of firmware blob */
    timer = fw->data[UCODE_SIZE * 4];
    bundle = fw->data[UCODE_SIZE * 4 + 1];
    min_size = fw->data[UCODE_SIZE * 4 + 2];

    /* Insert user-tunable settings in cb->u.ucode */
    cb->u.ucode[timer] &= cpu_to_le32(0xFFFF0000);
    cb->u.ucode[timer] |= cpu_to_le32(INTDELAY);
    cb->u.ucode[bundle] &= cpu_to_le32(0xFFFF0000);
    cb->u.ucode[bundle] |= cpu_to_le32(BUNDLEMAX);
    cb->u.ucode[min_size] &= cpu_to_le32(0xFFFF0000);
    cb->u.ucode[min_size] |= cpu_to_le32((BUNDLESMALL) ? 0xFFFF : 0xFF80);

    cb->command = cpu_to_le16(cb_ucode | cb_el);
    return 0;
}

static int e100_setup_iaaddr(struct nic *nic, struct cb *cb,
    struct sk_buff *skb)
{
    cb->command = cpu_to_le16(cb_iaaddr);
    memcpy(cb->u.iaaddr, nic->netdev->dev_addr, ETH_ALEN);
    return 0;
}

static int e100_dump(struct nic *nic, struct cb *cb, struct sk_buff *skb)
{
    cb->command = cpu_to_le16(cb_dump);
    cb->u.dump_buffer_addr = cpu_to_le32(nic->dma_addr +
        offsetof(struct mem, dump_buf));
    return 0;
}

static int e100_multi(struct nic *nic, struct cb *cb, struct sk_buff *skb)
{
    struct net_device *netdev = nic->netdev;
    struct netdev_hw_addr *ha;
    u16 i, count = min(netdev_mc_count(netdev), E100_MAX_MULTICAST_ADDRS);

    cb->command = cpu_to_le16(cb_multi);
    cb->u.multi.count = cpu_to_le16(count * ETH_ALEN);
    i = 0;
    netdev_for_each_mc_addr(ha, netdev) {
        if (i == count)
            break;
        memcpy(&cb->u.multi.addr[i++ * ETH_ALEN], &ha->addr,
            ETH_ALEN);
    }
    return 0;
}

