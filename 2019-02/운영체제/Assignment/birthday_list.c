#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
}

static LIST_HEAD(birthday_list);

int simple_init(void)
{
	struct birthday *p1;
	struct birthday *p2;
	struct birthday *p3;
	struct birthday *p4;
	struct birthday *p5;
	
	p1 = kmalloc(sizeof(*p1), GFP_KERNEL);
	p2 = kmalloc(sizeof(*p2), GFP_KERNEL);
	p3 = kmalloc(sizeof(*p3), GFP_KERNEL);
	p4 = kmalloc(sizeof(*p4), GFP_KERNEL);
	p5 = kmalloc(sizeof(*p5), GFP_KERNEL);

	p1->day = 12; p1->month = 1; p1->year = 1991;
	p2->day = 8; p1->month = 2; p1->year = 1993;
	p3->day = 3; p1->month = 5; p1->year = 1994;
	p4->day = 23; p1->month = 9; p1->year = 1997;
	p5->day = 30; p1->month = 11; p1->year = 1999;
	
	INIT_LIST_HEAD(&p1->list);
	INIT_LIST_HEAD(&p2->list);
	INIT_LIST_HEAD(&p3->list);
	INIT_LIST_HEAD(&p4->list);
	INIT_LIST_HEAD(&p5->list);
	
	list_add_tail(&p1->list, &birthday_list);
	list_add_tail(&p2->list, &birthday_list);
	list_add_tail(&p3->list, &birthday_list);
	list_add_tail(&p4->list, &birthday_list);
	list_add_tail(&p5->list, &birthday_list);
	
	printk(KERN_INFO "start traverse");
	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "[D-M-Y] : [%d, %d, %d]\n", ptr->day, ptr->month, ptr->year);
	}

	return 0;
}

void simple_exit(void)
{
	struct birthday *ptr, *next;
	
	list_for_each_entry_safe(ptr, next, &brthday_list, list)
	{
		printk(KERN_INFO "Remove : [%d, %d, %d]\n", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk(KERN_INFO "free memory\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("SGG");
