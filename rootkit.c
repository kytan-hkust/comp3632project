#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR(""); //
MODULE_DESCRIPTION(""); //
MODULE_VERSION("0.1");

// Hide this LKM rootkit itself
static void hide_itself() {
    ;
}

static int __init init_rootkit(void) {
    hide_itself();
    return 0;
}

static void __exit exit_rootkit(void) {
    ;
}

module_init(init_rootkit);
module_exit(exit_rootkit);