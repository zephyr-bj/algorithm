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
/**** another DIY method ****/
int short_irq;
int irq_probe_diy() {
	int trials[] = {3, 5, 7, 9, 0}; int tried[] = {0, 0, 0, 0, 0}; int i, count = 0;
	/*
	* install the probing handler for all possible lines. Remember
	* the result (0 for success, or -EBUSY) in order to only free
	* what has been acquired
	*/
	for (i = 0; trials[i]; i++)
		tried[i] = request_irq(trials[i], short_probing, SA_INTERRUPT, "short probe", NULL);
	do {
		short_irq = 0;         /* none got, yet */
		outb_p(0x10,short_base+2); /* enable */
		outb_p(0x00,short_base);
		outb_p(0xFF,short_base);     /* toggle the bit */
		outb_p(0x00,short_base+2); /* disable */
		udelay(5);              /* give it some time */
		/* the value has been set by the handler */ 
		if (short_irq == 0) {     /* none of them? */
			printk(KERN_INFO "short: no irq reported by probe\n");
		}
		/*
		* If more than one line has been activated, the result is
		* negative. We should service the interrupt (but the lpt port
		* doesn't need it) and loop over again. Do it at most 5 times
		*/
	} while (short_irq <=0 && count++ < 5);
	/* end of loop, uninstall the handler */
	for (i = 0; trials[i]; i++)
	if (tried[i] == 0) free_irq(trials[i], NULL);
	if (short_irq < 0)
		printk("short: probe failed %i times, giving up\n", count);
	return short_irq;
}
irqreturn_t short_probing(int irq, void *dev_id, struct pt_regs *regs){
	if (short_irq == 0) short_irq = irq;     /* found */
	if (short_irq != irq) short_irq = -irq;     /* ambiguous */ 
	return IRQ_HANDLED;
}
