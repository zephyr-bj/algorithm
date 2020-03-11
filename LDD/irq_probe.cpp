int irq_probe() {
	int short_irq=0;
	int count = 0;
	do {
		unsigned long mask;
		mask = probe_irq_on();
		outb_p(0x10,short_base+2); /* enable reporting */ 
		outb_p(0x00,short_base); /* clear the bit */ 
		outb_p(0xFF,short_base); /* set the bit: interrupt! */ 
		outb_p(0x00,short_base+2); /* disable reporting */ 
		udelay(5); /* give it some time */
		short_irq = probe_irq_off(mask);                        
		if (short_irq == 0) { /* none of them? */
			printk(KERN_INFO "short: no irq reported by probe\n"); 
			short_irq = -1;
		}
   		/*
   		* if more than one line has been activated, the result is
    	* negative. We should service the interrupt (no need for lpt port)
    	* and loop over again. Loop at most five times, then give up
    	*/
	} while (short_irq < 0 && count++ < 5);
	if (short_irq < 0)
		printk("short: probe failed %i times, giving up\n", count);
	return short_irq;
}
