/*
 * Project 4 Device Driver by
 * Louis Seefeld
 * No ill-use intended
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Louis Seefeld <lfs13@pitt.edu>");
MODULE_DESCRIPTION("\"Dice Driver\" minimal module");
MODULE_VERSION("dev");

/*
 * read is the function called when a process calls read() on
 * /dev/dice_driver.  It writes up to five random integers to the buffer passed in the
 * read() call.
 */

unsigned char get_random_byte(int max) {
         unsigned char c;
         get_random_bytes(&c, 1);
         return c%max;
}

static ssize_t read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
	int i = 0; /* loop counter */
	unsigned char * rand; /* pointer to new random bytes */ 
	

	/*
	 * If count == 0 then no work to be done.
	 * Else kmalloc count bytes from kernal.
	 */

	if (count == 0)
	{
		return 0;
	}
	rand = kmalloc(count, GFP_KERNEL);

	/* For loop putting count bytes into unsigned char array. */
	
	for(i = 0; i < count; i++)
        {
               rand[i]=get_random_byte(6) + 1;
        }
	
	
	
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	
	if (copy_to_user(buf, rand, count))
	{
		kfree(rand);
	}
	
	/* Tell the user how much data we wrote. */

	*ppos += count;

	return *ppos;
}



/*
 * The only file operation we care about is read.
 */

static const struct file_operations dice_driver_fops = {
	.owner		= THIS_MODULE,
	.read		= read,
};

static struct miscdevice dice_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/dice_driver.
	 */
	"dice_driver",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_driver_fops
};

static int __init dice_driver_init(void)
{
	int ret;

	/*
	 * Create the "dice_driver" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/dice_driver device using
	 * the default rules.
	 */

	ret = misc_register(&dice_dev);
	if (ret)
		printk(KERN_ERR "Unable to register \"Dice Driver\" misc device\n");

	return ret;
}

module_init(dice_driver_init);

static void __exit
dice_driver_exit(void)
{
	misc_deregister(&dice_dev);
}

module_exit(dice_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Louis Seefeld <lfs13@pitt.edu>");
MODULE_DESCRIPTION("\"Dice Driver\" minimal module");
MODULE_VERSION("dev");
