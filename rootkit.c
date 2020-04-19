#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int __init f(void) {
    return 0;
}

static void __exit g(void) {
    ;
}

module_init(f);
module_exit(g);