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

#define CSEMAD_LED_MAJOR 260
#define CSEMAD_LED_NAME "csemad_led"
#define CSEMAD_LED_ADDRESS 0x08000016

static int ledport_usage = 0;
//static unsigned char *csemad_led_data;
static unsigned char *csemad_led_addr;

//function name
ssize_t csemad_led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what);
ssize_t csemad_led_read(struct file *inode, char *gdata, size_t length, loff_t *off_what);
int csemad_led_open(struct inode *minode, struct file *mfile);
int csemad_led_release(struct inode *minode, struct file *mfile);

struct file_operations csemad_led_fops =
{
				.owner = THIS_MODULE,
				.open = csemad_led_open,
				.write = csemad_led_write,
				.read = csemad_led_read,
				.release = csemad_led_release,
};

int __init csemad_led_init(void)
{
				int result;

				result = register_chrdev(CSEMAD_LED_MAJOR, CSEMAD_LED_NAME, &csemad_led_fops);

				if(result < 0){
								printk(KERN_WARNING "Can't get any major!\n");
								return result;
				}

				csemad_led_addr = ioremap(CSEMAD_LED_ADDRESS, 1);
				if(csemad_led_addr == NULL)
				{
								printk("ioremap failed!\n");
								printk(KERN_ALERT "LED addr is not opend\n");
								return -1;
				}
				else
								printk(KERN_ALERT "Led addr success\n");

				return 0;
}

void __exit csemad_led_exit(void){
				iounmap(csemad_led_addr);
				unregister_chrdev(CSEMAD_LED_MAJOR, CSEMAD_LED_NAME);
				printk(KERN_ALERT "Good bye\n");
}

ssize_t csemad_led_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what)
{
				if(copy_from_user(csemad_led_addr, gdata, 1) != 0)
				{
								printk(KERN_ALERT "error write");
								return -EFAULT;
				}
				
				printk(KERN_ALERT "write success\n");

				return length;
}

ssize_t csemad_led_read(struct file *inode, char *gdata, size_t length, loff_t *off_what)

{
				if(copy_to_user(gdata, csemad_led_addr, length)!= 0)
				{
								printk(KERN_ALERT "error read");
								return -EFAULT;
				}
				return length;
}							
//0411

int csemad_led_open(struct inode *minode, struct file *mfile)
{
				if(ledport_usage != 0)
								return -EBUSY;
				ledport_usage = 1;
				
				printk(KERN_ALERT "open success\n");
				
				return 0;
}

int csemad_led_release(struct inode *minode, struct file *mfile)
{
				ledport_usage = 0;
				printk(KERN_ALERT "release success\n");

				return 0;
}

module_init(csemad_led_init);
module_exit(csemad_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEMAD");
