#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/fs.h>
MODULE_LICENSE("Dual BSD/GPL");
struct runner_t{
  int time; //stored in hundredths of seconds to avoid floats
  struct list_head runners;
};
static int myopen(struct inode *, struct file *);
static int myclose (struct inode *, struct file *);
static ssize_t myread(struct file *, int *, size_t, loff_t *);
static ssize_t mywrite(struct file *, const int *,size_t,  loff_t *);
void addRunner(int );

static struct file_operations fops = {
  .open = myopen,
  .release = myclose,
  .read = myread,
  .write = mywrite,
};

struct runner_t head;

void addRunner(int intime){
  struct runner_t *newrunner = kmalloc(sizeof(struct runner_t), GFP_KERNEL);
  newrunner->time = intime;
  INIT_LIST_HEAD(&(newrunner->runners));
  list_add_tail(&(newrunner->runners), &head.runners);
}

static int __init mod6_init(void){
  int val = register_chrdev(65, "assignment6", &fops);
  if(val < 0)
    printk(KERN_ALERT "Registration of driver failed with error %d", val);
  else
    printk(KERN_ALERT "Device successfully registered");
  INIT_LIST_HEAD(&(head.runners));
  return val; 
}
static int myclose(struct inode *mynode, struct file *myfile){
  printk(KERN_INFO "closing driver");
  return 0;
}
static int myopen(struct inode *mynode, struct file *myfile){
  printk(KERN_INFO "driver opened");
  return 0;
}


static void __exit mod6_exit(void){
  struct runner_t *temp, *pos;
  list_for_each_entry_safe(temp, pos, &(head.runners), runners){
    list_del(&(temp->runners));
    kfree(temp);
  }
  printk(KERN_INFO "removing driver");
  unregister_chrdev(65, "assignment6");
}

static ssize_t myread(struct file *myfile, int *buf, size_t length, loff_t *offset){
  struct runner_t *temp;
  list_for_each_entry(temp, &head.runners, runners){
    put_user(temp->time, buf++);
    printk("value of int is %d\n", temp->time);
  }
  return length;
}
static ssize_t mywrite(struct file *myfile, const int *buf, size_t length, loff_t *offset){
  if(*buf == 0){
    struct runner_t *temp, *pos;
    list_for_each_entry_safe(temp, pos, &(head.runners), runners){
      list_del(&(temp->runners));
      kfree(temp);
  }
  printk(KERN_INFO "cleared list");
  }
  else{
	addRunner(*buf);
    return 0;
  }
}


module_init(mod6_init);
module_exit(mod6_exit);
