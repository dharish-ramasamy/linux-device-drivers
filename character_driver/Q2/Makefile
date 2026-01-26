obj-m := dynamic_number.o

KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

install:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules_install
