/*select/poll relies on kernel notification for ready file deskriptors. 
 *But select/poll block as soon they are called, because the Systemcall-Handler runs in the Kernel-Space.
 *
 *Real asynchronous I/O is achieved via LibAIO (on Linux) and IOCP on Windows. 
 *They dont block the calling process/thread in der User Space and they allow real overlapped I/O.
 */
/*
 * 1.When F_SETOWN is invoked, nothing happens, except that a value is assigned to filp->f_owner.
 * 2.When F_SETFL is executed to turn on FASYNC, the driver’s fasync method is called. 
 */
struct scull_pipe {
  wait_queue_head_t inq, outq;/* read and write queues */
  char *buffer, *end;        /* begin of buf, end of buf */
  int buffersize;            /* used in pointer arithmetic */
  char *rp, *wp;            /* where to read, where to write */
  int nreaders, nwriters;    /* number of openings for r/w */
  struct fasync_struct *async_queue; /* asynchronous readers */
  struct semaphore sem;              /* mutual exclusion semaphore */
  struct cdev cdev;                  /* Char device structure */
};

static int scull_p_fasync(int fd, struct file *filp, int mode){
  struct scull_pipe *dev = filp->private_data;
  return fasync_helper(fd, filp, mode, &dev->async_queue);
}
static void scull_p_open(struct inode *inode, struct file *filp){
  struct scull_pipe *dev = hwinfo + MINOR(inode->i_rdev);
  request_irq(dev->irq, 
              sample_interrupt,
              0 /* flags */, 
              "sample", 
              dev /* dev_id */);
  /*....*/
  return 0;
}
irqreturn_t short_interrupt(int irq, void *dev_id, struct pt_regs *regs){
  struct scull_pipe *dev = dev_id;
  /* schedule bottom half to copy data 
   * ......
   */
  if (dev->async_queue)
    kill_fasync(&dev->async_queue, SIGIO, POLL_IN);

  return IRQ_HANDLED;
}

/*      in the user space        */
void input_handler(int signum){
	// process the async data
}
void main () {
  // kill_fasync will trigger the input_handler asynchoronously
  signal(SIGIO, &input_handler);
  /*  start a thread to waiting for signal arriave */
  fcntl(STDIN_FILENO, F_SETOWN, getpid());
  oflags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
  /*  do what you want to do  */
}
