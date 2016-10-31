obj-m := memchar.o
module-objs := memchar.o
PWD := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build

all:
    $(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
    rm -f *.o *.ko *.mod.c .memchar*
