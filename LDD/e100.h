// define struct cb; struct nic; struct rx;
/ nic.rxs points to a ring of rx structs, prev pointer of the first elements points to th last elements, 
next pointer of the last element 
struct nic {
    /* Begin: frequently used values: keep adjacent for cache effect */
    u32 msg_enable              ____cacheline_aligned;
    struct net_device *netdev;
    struct pci_dev *pdev;
    u16 (*mdio_ctrl)(struct nic *nic, u32 addr, u32 dir, u32 reg, u16 data);

    struct rx *rxs              ____cacheline_aligned;
    struct rx *rx_to_use;
    struct rx *rx_to_clean;
    struct rfd blank_rfd;
    enum ru_state ru_running;

    spinlock_t cb_lock          ____cacheline_aligned;
    spinlock_t cmd_lock;
    struct csr __iomem *csr;
    enum scb_cmd_lo cuc_cmd;
    unsigned int cbs_avail;
    struct napi_struct napi;
    struct cb *cbs;
    struct cb *cb_to_use;
    struct cb *cb_to_send;
    struct cb *cb_to_clean;
    __le16 tx_command;
    /* End: frequently used values: keep adjacent for cache effect */

    enum {
        ich                = (1 << 0),
        promiscuous        = (1 << 1),
        multicast_all      = (1 << 2),
        wol_magic          = (1 << 3),
        ich_10h_workaround = (1 << 4),
    } flags                 ____cacheline_aligned;

    enum mac mac;
    enum phy phy;
    struct params params;
    struct timer_list watchdog;
    struct mii_if_info mii;
    struct work_struct tx_timeout_task;
    enum loopback loopback;

    struct mem *mem;
    dma_addr_t dma_addr;
    struct pci_pool *cbs_pool;
    dma_addr_t cbs_dma_addr;
    u8 adaptive_ifs;
    u8 tx_threshold;
    u32 tx_frames;
    u32 tx_collisions;
    u32 tx_deferred;
    u32 tx_single_collisions;
    u32 tx_multiple_collisions;
    u32 tx_fc_pause;
    u32 tx_tco_frames;

    u32 rx_fc_pause;
    u32 rx_fc_unsupported;
    u32 rx_tco_frames;
    u32 rx_short_frame_errors;
    u32 rx_over_length_errors;

    u16 eeprom_wc;
    __le16 eeprom[256];
    spinlock_t mdio_lock;
    const struct firmware *fw;
};

//cb for command block ?
struct cb {
    __le16 status;
    __le16 command;
    __le32 link;
    union {
        u8 iaaddr[ETH_ALEN];
        __le32 ucode[UCODE_SIZE];
        struct config config;
        struct multi multi;
        struct {
            u32 tbd_array;
            u16 tcb_byte_count;
            u8 threshold;
            u8 tbd_count;
            struct {
                __le32 buf_addr;
                __le16 size;
                u16 eol;
            } tbd;
        } tcb; 
        __le32 dump_buffer_addr;
    } u;
    struct cb *next, *prev;
    dma_addr_t dma_addr;
    struct sk_buff *skb;
};

struct rx {
    struct rx *next, *prev;
    struct sk_buff *skb;
    dma_addr_t dma_addr;
};

struct rfd {
    __le16 status;
    __le16 command;
    __le32 link;
    __le32 rbd;
    __le16 actual_size;
    __le16 size;
};

/* CSR (Control/Status Registers) */
struct csr {
    struct {
        u8 status;
        u8 stat_ack;
        u8 cmd_lo;
        u8 cmd_hi;
        u32 gen_ptr;
    } scb;
    u32 port;
    u16 flash_ctrl;
    u8 eeprom_ctrl_lo;
    u8 eeprom_ctrl_hi;
    u32 mdi_ctrl;
    u32 rx_dma_count;
};

