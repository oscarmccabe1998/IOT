/*
======================================================================
Name		:interrupt.c
Author		:Oscar McCabe
Version		:0.1
Copyright	:Abertays one
Description	:Interupt for the raspberry pi zero
======================================================================
*/
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

static bool	State = 0;
static unsigned int Led = 23;
static unsigned int Button = 16;
static unsigned int Irqnum = 0;
static unsigned int Counter = 0;


/*  Handle interrupt  - button push event */
static irq_handler_t piirq_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs){
   State = !State; /* Toogle LED */
   gpio_set_value(Led, State);

   printk(KERN_INFO "piirq: led state is : [%d] ", gpio_get_value(Led));
   printk(KERN_INFO "piirq: button state is : [%d] ", gpio_get_value(Button));

   Counter++;
   return (irq_handler_t) IRQ_HANDLED;
}
int __init piirq_init(void){
	int result = 0;
    pr_info("%s\n", __func__);
    /* https://www.kernel.org/doc/Documentation/pinctrl.txt */
	printk("piirq: IRQ Test");
    printk(KERN_INFO "piirq: Initializing driver\n");

    if (!gpio_is_valid(Led)){
    	printk(KERN_INFO "piirq: invalid GPIO\n");
    return -ENODEV;
   }

	   gpio_request(Led, "Led");
	   gpio_direction_output(Led, 1);
	   /* Make it appear in /sys/class/gpio/gpio16 for echo 0 > value */
	   gpio_export(Led, false);
	   gpio_request(Button, "Button");
	   gpio_direction_input(Button);
	   gpio_set_debounce(Button, 500); /* Adjust this number to sync with circut */
	   gpio_export(Button, false);


    Irqnum = gpio_to_irq(Button);
    printk(KERN_INFO "piirq: The button is mapped to IRQ: %d\n", Irqnum);

    result = request_irq(Irqnum,
		  (irq_handler_t) piirq_irq_handler, /* pointer to the IRQ handler method */
		  IRQF_TRIGGER_RISING,
		  "piirq_handler",    /* See this string from user console to identify: cat /proc/interrupts */
		  NULL);

    printk("piirq loaded\n");
    return 0;
}
void __exit piirq_exit(void){
   gpio_set_value(Led, 0);
   gpio_unexport(Led);
   free_irq(Irqnum, NULL);
   gpio_unexport(Button);
   gpio_free(Led);
   gpio_free(Button);
   printk("piirq unloaded\n");
}
module_init(piirq_init);
module_exit(piirq_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oscar McCabe");
MODULE_DESCRIPTION("RPi IRQ Test");
MODULE_VERSION("0.1");
