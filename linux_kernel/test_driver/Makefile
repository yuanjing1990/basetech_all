ifeq ($(KERNELRELEASE),)
	KVERSION = $(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) clean

modules_install:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules_install

else
	obj-m :=test.o
endif
