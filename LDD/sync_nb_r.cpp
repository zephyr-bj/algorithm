static unsigned int scull_p_poll(struct file *filp, poll_table *wait){
  struct scull_pipe *dev = filp->private_data;
  unsigned int mask = 0;
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

/* at the user code side */

#include <sys/time.h> 
#include <sys/types.h> 
#include <unistd.h>

int main(void)
{
    struct timeval tv;
    fd_set readfds;
    fd_set master;
    tv.tv_sec = 2; 
    tv.tv_usec = 500000;
  
    int fd = open(/dev/scullpipe, O_RDWR);
    if(fd < 0) {
        printf("Can not open the device file\n");
        exit(1);
    }
    FD_ZERO(&readfds); 
    FD_ZERO(&master); 
    FD_SET(fd, &master);
  
    char buffer[1024];
    int length = 1024;
    int sz;

    for(;;) {
        read_fds = master; // copy it
        if (select(fd+1, &read_fds, NULL, NULL, tv) == -1) {
            perror("select");
            exit(4); 
        }
        if (FD_ISSET(fd, &read_fds)) { 
            sz = read(fd, buffer, length);
        }
    }
    return 0; 
}
