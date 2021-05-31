//get_user_pages: http://www.hep.by/gnu/kernel/kernel-api/API-get-user-pages.html
// Returns number of pages pinned. This may be fewer than the number requested. If nr_pages is 0 or negative, returns 0. If no pages were pinned, returns -errno. Each page returned must be released with a put_page call when it is finished with. vmas will only remain valid while mmap_sem is held.

// Must be called with mmap_sem held for read or write.

// get_user_pages walks a process's page tables and takes a reference to each struct page that each user address corresponds to at a given instant. 
// That is, it takes the page that would be accessed if a user thread accesses the given user virtual address at that instant.


//the code below copied from https://gist.github.com/17twenty/2930467
//show an example to use "get_user_pages"
//get_user_pages/gu_page.c	2012-06-14 14:41:31.797310260 +0100
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

#include <linux/pagemap.h>

#define LED_MAJOR 42
#define DEVICE_NAME "simpleuser"

/*
 * Prototypes
 */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t * ppos);

static struct file_operations led_ops = {
	.owner    = THIS_MODULE,
	.open     = device_open,
	.release  = device_release,
	.write =	device_write
};

static struct class *mmap_class;

static int device_open(struct inode *inode, struct file *file)
{
	printk ("device_open: %d.%d\n", MAJOR (inode->i_rdev),
		 MINOR (inode->i_rdev));
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("device_release: %d.%d\n", MAJOR (inode->i_rdev),
		 MINOR (inode->i_rdev));
	return 0;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t * ppos)
{
    int res;
    unsigned long uaddr;
    char addrstr[80];
    struct page *page;
    char *my_page_address;

    unsigned long copied = copy_from_user(addrstr, buf, sizeof(addrstr));
    if (copied != 0)
    {
        pr_err("Told to copy %d, but only copied %lu\n", count, copied);
    }
    uaddr = simple_strtoul(addrstr, NULL, 0);
    
    down_read(&current->mm->mmap_sem);
	res = get_user_pages(current, current->mm,
		                 uaddr,
		                 1, /* Only want one page */
		                 1, /* Do want to write into it */
		                 1, /* do force */
		                 &page,
		                 NULL);
    if (res == 1) {
        pr_err("Got page\n");
        /* Do something with it */
        my_page_address = kmap(page);
        strcpy (my_page_address, "Hello, is it me you're looking for?\n");
        pr_err("Got address %p and user told me it was %lx\n",my_page_address, uaddr);
        pr_err("Wrote: %s", my_page_address);
        
        kunmap(page);
        
        /* Clean up */
        if (!PageReserved(page))
            SetPageDirty(page);
	    page_cache_release(page);
    } else {
        pr_err("Couldn't get page :(\n");
    }
	up_read(&current->mm->mmap_sem);
    
    return count;
}

static int __init el504_init(void)
{
	int ret ;
	
	/* Register the character device */
	ret = register_chrdev (LED_MAJOR, DEVICE_NAME, &led_ops);
	if (ret < 0) {
		pr_alert("el504_init: failed with %d\n", ret);
		return ret;
	}

	mmap_class = class_create (THIS_MODULE, "mmap");
	device_create (mmap_class, NULL, MKDEV (LED_MAJOR, 0), NULL, "mmap");
	return 0;
}

static void __exit el504_exit(void)
{
	pr_debug("Goodbye\n");
	device_destroy (mmap_class, MKDEV (LED_MAJOR, 0));
	class_destroy (mmap_class);
	unregister_chrdev (LED_MAJOR, DEVICE_NAME);
}

module_init (el504_init);
module_exit (el504_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Nick Glynn");
MODULE_DESCRIPTION ("Example for get_user_pages()");

//get_user_pages/Makefile	2012-06-14 14:21:11.271274011 +0100
obj-m += gu_page.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean 

// get_user_pages/userspace/Makefile	2012-06-14 14:53:29.528816418 +0100
BIN := userspace
OBJECTS += $(BIN).c

all:
	gcc $(OBJECTS) -o $(BIN)

clean:
	rm $(BIN)

// get_user_pages/userspace/userspace.c	2012-06-14 14:47:25.754137234 +0100
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int mh, res;
       char addrstr[80];
	char *ptr, *bp;
	const char *string = "Testing page";

	printf ("%s\n", argv[0]);
	if (argc < 2)
	{
		printf ("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	mh = open (argv [1], O_RDWR);
	if (mh == -1)
	{
		printf ("Unable to open '%s'\n", argv [1]);
		return 1;
	}
	/* Grab a page of memory (4096) and sprintf into it */
	
	res = posix_memalign((void **)&ptr, 4096, 4096);

	if (NULL != ptr)
	{
	    sprintf(ptr, "%s", string);
	
	    bp = ptr;
	
	    /* Do a write to the kernel at which point it should mess with it */
	    sprintf(addrstr, "%p", ptr);
	    printf("Telling kernel it is %p\n", ptr);
           res = write(mh, addrstr, strlen(addrstr));
	
	    /* See what lives there still */
	    printf ("Marker text 1: %s\n", ptr);
	    printf ("ptr = %p, bp = %p\n", ptr, bp);

    }
    close (mh);
	return 0;
}
