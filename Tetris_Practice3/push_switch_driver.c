#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/version.h>

#define CSEMAD_PUSH_SWITCH_MAJOR 265
#define CSEMAD_PUSH_SWITCH_NAME "csemad_push_switch"
#define CSEMAD_PUSH_SWITCH_ADDRESS 0x08000050

static int pushport_usage = 0;
static unsigned char *csemad_push_switch_addr;
unsigned char swmax[9];

ssize_t csemad_push_switch_read(struct file *inode, char *gdata, size_t length,loff_t *off_what);
int csemad_push_switch_open(struct inode *minode, struct file *mfile);
int csemad_push_switch_release(struct inode *minode, struct file *mfile);
int __init csemad_push_switch_init(void);
void __exit csemad_push_switch_exit(void);


//structure def
struct file_operations csemad_push_switch_fops =
{
        .owner = THIS_MODULE,
        .open = csemad_push_switch_open,
        .read = csemad_push_switch_read,
        .release = csemad_push_switch_release,
};

int __init csemad_push_switch_init(void)
{
        int result;
        
        result = register_chrdev(CSEMAD_PUSH_SWITCH_MAJOR, CSEMAD_PUSH_SWITCH_NAME, &csemad_push_switch_fops);
        if(result < 0)
        {
                printk(KERN_WARNING "Can't get any major!\n");
                return result;
        }

        csemad_push_switch_addr = ioremap(CSEMAD_PUSH_SWITCH_ADDRESS, 1);

        if(csemad_push_switch_addr == NULL)
        {
                printk("ioremap failed!\n");
                printk(KERN_ALERT "Push switch addr is not opened\n");
                return -1;
        }
        else
                printk(KERN_ALERT "Push switch addr success\n");

        return 0;
}

void __exit csemad_push_switch_exit(void)
{
        iounmap(csemad_push_switch_addr);
        unregister_chrdev(CSEMAD_PUSH_SWITCH_MAJOR, CSEMAD_PUSH_SWITCH_NAME);
        printk(KERN_ALERT "Good bye\n");
}

ssize_t csemad_push_switch_read(struct file *inode, char *gdata, size_t length, loff_t *off_what)
{
        int i;

				for(i=0; i<9; i++)
				{
								swmax[i] = inb((unsigned int)csemad_push_switch_addr + i*2);
								printk(KERN_ALERT "[%d] = %d\n", i , swmax[i]);
				}
				if(copy_to_user(gdata, swmax, length) != 0)
							return -EFAULT;
				return length;	
}

int csemad_push_switch_open(struct inode *minode, struct file *mfile)
{
        if(pushport_usage != 0)
                return -EBUSY;
        pushport_usage = 1;

        printk(KERN_ALERT "open success\n");

        return 0;
}

int csemad_push_switch_release(struct inode *minode, struct file *mfile)
{
        pushport_usage = 0;
        printk(KERN_ALERT "release success\n");

        return 0;
}

module_init(csemad_push_switch_init);
module_exit(csemad_push_switch_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEMAD");
