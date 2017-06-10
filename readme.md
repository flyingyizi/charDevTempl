

## fsOperation template  

/*---------------usage-------------------*/
1. according to your requirement, to rewrite belows functions contents in fsOperation_templ.c
```c
long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
                   loff_t *f_pos);
ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
                   loff_t *f_pos);
loff_t  scull_llseek(struct file *filp, loff_t off, int whence);
```
2. in the main moulde, call initCharDevWithFops to init the cdev


##  proc template

/*---------------usage-------------------*/
1. according to your requirement, to rewrite belows functions contents in proc_templ.c
```c
 void *scull_seq_start(struct seq_file *s, loff_t *pos)
 void *scull_seq_next(struct seq_file *s, void *v, loff_t *pos)
 void scull_seq_stop(struct seq_file *s, void *v)
 int scull_seq_show(struct seq_file *s, void *v)
```
2. in the main moulde, call scull_create_proc, scull_remove_proc to init the cdev

void scull_create_proc(void);

void scull_remove_proc(void);


