/*
 *
 */
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <asm/uaccess.h>	/* copy_*_user */  //access_ok
#include <linux/cdev.h>

#include <linux/fs.h>		/* everything... */
#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */


#include "ioctl_tmpl.h"		
#include "scull.h"		     //struct scull_dev



/*
 * The ioctl() implementation
 */

static long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	//ToBe implement

	int err = 0;
	int retval = 0;
    
	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
    //ToBe implement
	  //case SCULL_IOCTQSET:
		//if (! capable (CAP_SYS_ADMIN))
		//	return -EPERM;
		//scull_qset = arg;
		//break;

	  //case SCULL_IOCGQSET:
		//retval = __put_user(scull_qset, (int __user *)arg);
		//break;
		
	  //case SCULL_IOCSQSET:
		//if (! capable (CAP_SYS_ADMIN))
		//	return -EPERM;
		//retval = __get_user(scull_qset, (int __user *)arg);
		//break;

	  default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;

}



/*
 * Open and close
 */

static int scull_open(struct inode *inode, struct file *filp)
{
	//ToBe implement
	
	
	struct scull_dev *dev; /* device information */

	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev; /* for other methods */

	/* now trim to 0 the length of the device if open was write-only */
	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) {
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
		up(&dev->sem);
	}
	return 0;          /* success */
}

int scull_release(struct inode *inode, struct file *filp)
{
	//ToBe implement
	
	
	return 0;
}

/*
 * Data management: read and write
 */
static ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
                loff_t *f_pos)
{
	//ToBe implement
	
	
	struct scull_dev *dev = filp->private_data; 
	ssize_t retval = 0;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;

	//if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
	//	retval = -EFAULT;
	//	goto out;
	//}
	//*f_pos += count;
	//retval = count;

  out:
	up(&dev->sem);
	return retval;
}


static ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *f_pos)
{
	//ToBe implement
	
	
	
	struct scull_dev *dev = filp->private_data;

	ssize_t retval = -ENOMEM; /* value used in "goto out" statements */

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	//if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count)) {
	//	retval = -EFAULT;
	//	goto out;
	//}
	//*f_pos += count;
	//retval = count;

   /* update the size */
	if (dev->size < *f_pos)
		dev->size = *f_pos;

  //out:
	up(&dev->sem);
	return retval;
}




/*
 * The "extended" operations -- only seek
 */

static loff_t scull_llseek(struct file *filp, loff_t off, int whence)
{
	//ToBe implement
	
	
	struct scull_dev *dev = filp->private_data;
	loff_t newpos;

	switch(whence) {
	  case 0: /* SEEK_SET */
		newpos = off;
		break;

	  case 1: /* SEEK_CUR */
		newpos = filp->f_pos + off;
		break;

	  case 2: /* SEEK_END */
		newpos = dev->size + off;
		break;

	  default: /* can't happen */
		return -EINVAL;
	}
	if (newpos < 0) return -EINVAL;
	filp->f_pos = newpos;
	return newpos;
}




struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
	.llseek =   scull_llseek,
	.read =     scull_read,
	.write =    scull_write,
	.unlocked_ioctl = scull_ioctl,
	.open =     scull_open,
	.release =  scull_release,
};


/*
 * Init char_dev structure with file operations
 */
void initCharDevWithFops(struct cdev *chardev)
{ 
	if (NULL == chardev) {
				chardev = cdev_alloc();
	} else {	 
				cdev_init(chardev, &scull_fops);
  }
	chardev->owner = THIS_MODULE;
	chardev->ops = &scull_fops;
}
