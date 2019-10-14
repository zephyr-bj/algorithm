static unsigned int scull_p_poll(struct file *filp, poll_table *wait){
  struct scull_pipe *dev = filp->private_data;
  unsigned int mask = 0;
  /*
   * The buffer is circular; it is considered full
   * if "wp" is right behind "rp" and empty if the
   * two are equal.
   */
  down(&dev->sem);
  poll_wait(filp, &dev->inq,  wait);/* readable */
  poll_wait(filp, &dev->outq, wait);/* writable */
  if (dev->rp != dev->wp)
    mask |= POLLIN | POLLRDNORM;
  if (spacefree(dev))
    mask |= POLLOUT | POLLWRNORM;
  up(&dev->sem);

  return mask;
}

/* at the user code side, the example below has nothing to do the driver function above
because the conventional programs available to a shell don’t perform nonblocking operations. 
The misc-progs source directory contains the following simple program, called nbtest, for testing nonblocking operations. 
All it does is copy its input to its output, using nonblocking I/O and delaying between retries. 
The delay time is passed on the command line and is one second by default.
*/

int main(int argc, char **argv)
{
  int delay = 1, n, m = 0;

  if (argc > 1)
  delay=atoi(argv[1]);

  fcntl(0, F_SETFL, fcntl(0,F_GETFL) | O_NONBLOCK); /* stdin */
  fcntl(1, F_SETFL, fcntl(1,F_GETFL) | O_NONBLOCK); /* stdout */

  while (1) {
    n = read(0, buffer, 4096);
    if (n >= 0)
      m = write(1, buffer, n);
    if ((n < 0 || m < 0) && (errno != EAGAIN))
      break;
    sleep(delay);
  }
  perror(n < 0 ? "stdin" : "stdout");
  exit(1);
}    
