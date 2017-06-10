/*
 * 
 *
 *
 */
#include <linux/proc_fs.h>
#include <asm/uaccess.h>	/* copy_*_user */
#include <linux/seq_file.h>


static void *scull_seq_start(struct seq_file *s, loff_t *pos)
{
	//ToBe implement
	return NULL;
}

static void *scull_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	//ToBe implement
	return NULL;
}

static void scull_seq_stop(struct seq_file *s, void *v)
{
	/* Actually, there's nothing to do here */
	//ToBe implement. 
	return ;
	
}

static int scull_seq_show(struct seq_file *s, void *v)
{
	//ToBe implement
	return 0;
}
	
/*
 * Tie the sequence operators up.
 */
static struct seq_operations scull_seq_ops = {
	.start = scull_seq_start,
	.next  = scull_seq_next,
	.stop  = scull_seq_stop,
	.show  = scull_seq_show
};

static int scullmem_proc_open(struct inode *inode, struct file *file)
{
	//ToBe implement
    return 0;	
}

static int scullseq_proc_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &scull_seq_ops);
}

/*
 * Create a set of file operations for our proc files.
 */
static struct file_operations scullmem_proc_ops = {
	.owner   = THIS_MODULE,
	.open    = scullmem_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release
};

static struct file_operations scullseq_proc_ops = {
	.owner   = THIS_MODULE,
	.open    = scullseq_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};
	

/*
 * Actually create (and remove) the /proc file(s).
 */

void scull_create_proc(void)
{
	proc_create_data("scullmem", 0 /* default mode */,
			NULL /* parent dir */, &scullmem_proc_ops,
			NULL /* client data */);
	proc_create("scullseq", 0, NULL, &scullseq_proc_ops);
}

void scull_remove_proc(void)
{
	/* no problem if it was not registered */
	remove_proc_entry("scullmem", NULL /* parent dir */);
	remove_proc_entry("scullseq", NULL);
}





