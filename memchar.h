#ifndef __MEMCHAR_H_
#define __MEMCHAR_H_

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#ifndef MEMCHAR_MAJOR
#define MEMCHAR_MAJOR 0
#endif

ssize_t memchar_read(struct file*, char __user*, size_t, loff_t*);
ssize_t memchar_write(struct file*, const char __user*, size_t, loff_t*);
int memchar_open(struct inode*, struct file*);
int memchar_release(struct inode*, struct file*);

struct file_operations memchar_fops = {
    .owner = THIS_MODULE,
    .read = memchar_read,
    .write = memchar_write,
    .open = memchar_open,
    .release = memchar_release,
};

struct memchar_dev {
    struct cdev cdev;
};

#endif