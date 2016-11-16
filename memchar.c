#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include "memchar.h"

MODULE_LICENSE("Dual BSD/CPL");

int memchar_major = MEMCHAR_MAJON;
int memchar_minor = 0;

struct memchar_dev* devices;

int memchar_open(struct inode* inode, struct file* filp) {
    return 0;
}

int memchar_release(struct inode* inode, struct file* filp) {
    return 0;
}

ssize_t memchar_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    return 0;
}

ssize_t memchar_write(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {
    return 0;
}

static void memchar_setup_cdev(struct memchar_dev* dev) {
    int err, devno = MKDEV(memchar_major, memchar_minor);
    cdev_init(&dev->cdev, &memchar_fops);
    err = cdev_add(&dev->cdev, devno, 1);
    if (err) {
        printk(KERN_NOTICE "Error %d adding memchar", err);
    }
}

static void memchar_cleanup_module() {
    dev_t devno = MKDEV(memchar_major, memchar_minor);
    cdev_del(&memchar_dev->cdev);
    kfree(memchar_dev);
    unregister_chrdev_region(devno, 1);
}

/*static int memchar_major, memchar_minor; */

static int memchar_init(void) {
    int ret;
    dev_t dev;
    
    if (memchar_major) {
        dev = MKDEV(memchar_major, memchar_minor);
        ret = register_chrdev_region(dev, 1, "memchar");
    } else {
        ret = alloc_chrdev_region(&dev, memchar_minor, 1, "memchar");
        if (ret < 0) {
            printk(KERN_WARNING "memchar: can't get major %d\n", mem_major);
            return ret;
        }
        memchar_major = MAJOR(dev);
    }

    /* allocate the device */
    devices = kmalloc(sizeof(struct memchar_dev), GFP_KERNEL);
    if (!devices) {
        ret = -ENOMEM;
        goto fail; 
    } 
    memset(devices, 0, sizeof(struct memchar_dev));
    memchar_setup_cdev(devices);

    printk(KERN_INFO "memchar module has been inited");
    return 0;
fail:
    memchar_cleanup_module();
    return ret;
}

static int memchar_exit(void) {
    scull_cleanup_module();
    printk(KERN_INFO "memchar module has been exited");
    return 0;
}



module_init(memchar_init);
module_exit(memchar_exit);