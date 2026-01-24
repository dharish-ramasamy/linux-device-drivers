obj-m := sum_module.o

KERNSRC := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

modules:
	make -C $(KERNSRC) M=$(PWD) modules

module_install:
	make -C $(KERNSRC) M=$(PWD) modules_install
	depmod -a

clean:
	make -C $(KERNSRC) M=$(PWD) clean
