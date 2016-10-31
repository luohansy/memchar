#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/CPL");

/*static int memchar_major, memchar_minor; */

static int memchar_init(void) {
    printk(KERN_INFO "memchar module has been inited");
    return 0;
}

static int memchar_exit(void) {
    printk(KERN_INFO "memchar module has been exited");
    return 0;
}

module_init(memchar_init);
module_exit(memchar_exit);