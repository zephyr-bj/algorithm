/* for dynamic initialization
wait_queue_head_t wq;
init_waitqueue_head(&wq);
*/
/*
 In the sample source, you can find a module called sleepy. It implements a device with simple behavior: 
 any process that attempts to read from the device is put to sleep. 
 Whenever a process writes to the device, all sleeping processes are awakened. 
 This behavior is implemented with the following read and write methods:
*/
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;
ssize_t sleepy_read (struct file *filp, char __user *buf, size_t count, loff_t *pos) {
  wait_event_interruptible(wq, flag != 0);
  flag = 0;
  return 0; /* EOF */
}
                        
ssize_t sleepy_write (struct file *filp, const char __user *buf, size_t count, loff_t *pos) {
  flag = 1;
  wake_up_interruptible(&wq);
  return count; /* succeed, to avoid retrial */
}

/* The condition is an arbitrary boolean expression that is evaluated by the macro before and after sleeping; 
   until condition evaluates to a true value, the process continues to sleep. 
   Note that condition may be evaluated an arbitrary number of times.
*/
