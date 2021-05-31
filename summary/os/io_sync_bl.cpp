/* complete version of synchronous read and write, works for:
   the no data case
   the multiple read clients case (wait_event_interruptible waken up, return zero, but see empty, dev->rp == dev->wp again)
*/

struct my_x_dev {
    in_db *inque;
    int inhead, intail, insz;
    wait_queue_head_t inwq;
    spinlock_t inlock;
    struct tasklet_struct in_tasklet;
    
    out_db * outque;
    int outhead, outtail, outsz;
    wait_queue_head_t outwq;
    spinlock_t outlock;
    
    struct hw_x_dev hdev;  
};

/*         read part         */
static ssize_t my_x_dev_read (struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct my_x_dev *dev = filp->private_data;
    unsigned long irqflags;
    spin_lock_irqsave(&dev->inlock, irqflags);
    while (dev->intail == dev->inhead) {
        spin_unlock_irqrestore(&dev->inlock,irqflags);
        if (filp->f_flags & O_NONBLOCK)
            return -EAGAIN;
        wait_event_interruptible(dev->inwq, (dev->intail != dev->inhead));
        spin_lock_irqsave(&dev->inlock,irqflags);
    }
    
    /* ok, data is there, return something */
    if (dev->inhead > dev->intail)count = min(count, (size_t)(dev->inhead - dev->intail));
    else count = min(count, (size_t)(dev->insz - dev->intail + 1));                        
    if (copy_to_user(buf, dev->inque+dev->intail, count*sizeof(in_db))) {
        spin_unlock_irqrestore(&dev->inlock,irqflags);
        return -EFAULT;
    }                        
    dev->inrp = (dev->inrp+count)%dev->insz;
    spin_unlock_irqrestore(&dev->inlock,ifqflags);
    return count;
}

static irqreturn_t my_x_dev_in_irs_fast(int irq, void *dev_id, struct pt_regs *regs)
{
    my_x_dev * dev = (my_x_dev*)dev_id;
    unsigned long irqflags;
    spin_lock_irqsave(&(dev->inlock),irqflags);
    dev->inhead = (dev->inhead+1)%dev->insz;
    if(dev->inhead == dev->intail) dev->intail = (dev->intail+1)%dev->insz;
    hw_get_data(dev->hdev, dev->inque+dev->inhead);
    spin_lock_irqrestore(&dev->inlock, irqflags);
    wake_up_interruptible(&dev->inq);
    return IRQ_HANDLED;
}

static irqreturn_t my_x_dev_in_irs_slow(int irq, void *dev_id, struct pt_regs *regs)
{
    my_x_dev * dev = (my_x_dev*)dev_id;
    tasklet_schedule(&dev->in_tasklet);
    return IRQ_HANDLED;
}
void my_x_dev_in_tasklet(unsigned long dev_id)
{
    my_x_dev * dev = (my_x_dev*)dev_id;
    unsigned long irqflags;
    spin_lock_irqsave(&(dev->inlock),irqflags);
    dev->inhead = (dev->inhead+1)%dev->insz;
    if(dev->inhead == dev->intail) dev->intail = (dev->intail+1)%dev->insz;
    hw_get_data(dev->hdev, dev->inque+dev->inhead);
    spin_lock_restore(&dev->inlock, irqflag);
}

/*            write part           */

/* How much space is free? */
static int spacefree(struct my_x_dev *dev)
{
    if (dev->outtail == dev->outhead) return dev->outsz - 1;
    return ((dev->outtail + dev->outsz - dev->outhead) % dev->outsz) - 1;
}
static ssize_t my_x_dev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    struct my_x_dev *dev = filp->private_data;
    int result;
    unsigned long irqflags;
    spin_lock_irqsave(&dev->outlock,irqflags);
    while (spacefree(dev) == 0) { /* full */ 
        spin_unlock_irqrestore(&dev->outlock,irqflags);
        if (filp->f_flags & O_NONBLOCK)
            return -EAGAIN;
        wait_event_interruptible(dev->outwq, (dev->outtail != dev->outhead+1));
        spin_lock_irqsave(&dev->outlock,irqflags);
    }

    count = min(count, (size_t)spacefree(dev));
    if (dev->outhead >= dev->outtail)count = min(count, (size_t)(dev->end - dev->outhead)); 
    else count = min(count, (size_t)(dev->outtail - dev->outhead - 1));
    if (copy_from_user(dev->outque+dev->outhead, buf, count*sizeof(out_db))) {
        spin_lock_irqrestore (&dev->outlock,irqflags);
        return -EFAULT;
    }
    dev->outhead += (dev->outhead+count)%dev->outsz;
    spin_lock_irqrestore(&dev->outlock,irqflags);
    hw_put_data(dev->outque+dev->outtail);
    return count;
}

static irqreturn_t my_x_dev_out_irs(int irq, void *dev_id, struct pt_regs *regs)
{
    my_x_dev * dev = (my_x_dev*)dev_id;
    unsigned long irqflags;
    spin_lock_irqsave(&(dev->outlock),irqflags);
    hw_put_data(dev->hdev, dev->inque+dev->intail);
    dev->outtail = (dev->outtail+1)%dev->insz;
    spin_lock_irqrestore(&dev->outlock,irqflags);
    wake_up_interruptible(&dev->outwq);
    return IRQ_HANDLED;
}
