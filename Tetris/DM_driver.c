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

//DM = dot matrix

#define CSEMAD_DM_MAJOR 262
#define CSEMAD_DM_NAME "csemad_DM"

#define CSEMAD_DM_ADDRESS 0x08000210

static int DM_port_usage = 0;
static unsigned char *csemad_DM_addr;

//function name
ssize_t csemad_DM_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what);
//ssize_t csemad_DM_read(struct file *inode, char *gdata, size_t length, loff_t *off_what);
int csemad_DM_open(struct inode *minode, struct file *mfile);
int csemad_DM_release(struct inode *minode, struct file *mfile);

struct file_operations csemad_DM_fops =
{
				.owner = THIS_MODULE,
				.open = csemad_DM_open,
				.write = csemad_DM_write,
				.release = csemad_DM_release,
};

int __init csemad_DM_init(void)
{
				int result;
								
				result = register_chrdev(CSEMAD_DM_MAJOR, CSEMAD_DM_NAME, &csemad_DM_fops);

				if(result < 0){
								printk(KERN_WARNING "Can't get any major!\n");
								return result;
				}

				csemad_DM_addr = ioremap(CSEMAD_DM_ADDRESS, 1);
				if(csemad_DM_addr == NULL)
				{
								printk("ioremap failed!\n");
								printk(KERN_ALERT "DM addr is not opend\n");
								return -1;
				}
				else
								printk(KERN_ALERT "DM addr success\n");

				return 0;
}

void __exit csemad_DM_exit(void){
				iounmap(csemad_DM_addr);
				unregister_chrdev(CSEMAD_DM_MAJOR, CSEMAD_DM_NAME);
				printk(KERN_ALERT "Good bye\n");
}

ssize_t csemad_DM_write(struct file *inode, const char *gdata, size_t length, loff_t *off_what)
{
				int i;
				
				for(i=0; i<10; i++)
				{
								if(copy_from_user(csemad_DM_addr + i*2, gdata + i, 1) != 0)
								{
												printk(KERN_ALERT "error write");
												return -EFAULT;
								}
				}
				
				//printk(KERN_ALERT "write success\n");

				return length;
}

int csemad_DM_open(struct inode *minode, struct file *mfile)
{
				if(DM_port_usage != 0)
								return -EBUSY;
				DM_port_usage = 1;
				
				printk(KERN_ALERT "open success\n");
				
				return 0;
}

int csemad_DM_release(struct inode *minode, struct file *mfile)
{
				DM_port_usage = 0;
				//printk(KERN_ALERT "release success\n");

				return 0;
}

module_init(csemad_DM_init);
module_exit(csemad_DM_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEMAD");
