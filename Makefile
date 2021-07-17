obj-m :=inser_module.o
obj-m +=char_device.o
obj-m +=jiffies.o

all:
      make -C /lib/modules/$(shell uname -r)/build M=$(shel pwd) modules
clean:
      make -C /lib/modules/$(shell uname -r)/build M=$(shel pwd) clean
