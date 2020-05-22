#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("kytan");
MODULE_DESCRIPTION("An LKM rootkit for COMP 3632");
MODULE_VERSION("0.1");


// Hide this LKM rootkit itself
static void hide_itself(void) {
    ;
}


// Unhide this LKM rootkit itself
static void unhide_itself(void) {
    ;
}


static int __init init_rootkit(void) {
    hide_itself();

    printk(KERN_INFO "[Exit] Init rootkit\n");
    return 0;
}


static void __exit exit_rootkit(void) {
    unhide_itself();

    printk(KERN_INFO "[Exit] Exit rootkit\n");
}


module_init(init_rootkit);
module_exit(exit_rootkit);