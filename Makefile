ifneq ($(KERNELRELEASE),)
	obj-m := assignment6.o

else
		KERNELDIR ?= \
		/lib/modules/`uname -r`/build/
		PWD := `pwd`

default:
		$(MAKE) -C $(KERNELDIR) \
		M=$(PWD) modules

endif

clean:
		rm -f *.ko *.o Module* *mod* assign6 user
		rmmod assignement6.ko
user:
		gcc user.c -o user
