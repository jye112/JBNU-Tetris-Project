obj-m += DM_driver.o push_switch_driver.o fpga_fnd_driver.o led_driver.o

PWD = $(shell pwd)

all: driver app

driver:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

app :
	gcc -W -fstack-protector -static -o tetris tetrisMain.c tetrisDM.c tetrisDriver.c -lpthread

clean:
	rm -rf *.ko *.mod.* *.o tetris Module.symvers modules.order .tetris* .tmp* tetris
