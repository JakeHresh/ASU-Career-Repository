/**
 * HreshchyshynLKM.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 *
 * This program is an implementation of an LKM that displays information about running processes, including parent and child processes.
 *
 * Time Spent: 5 hours
 * @author Jacob Hreshchyshyn, Above authors of Operating System Concepts
 * @version 1.0
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/sched/signal.h>
#include <linux/moduleparam.h>

/* This function is called when the module is loaded. */
int pid = 0;
module_param(pid, int, 0);
int simple_init(void)
{
    //MODULE_PARM(pid, "i");
    printk(KERN_INFO "Loading Module\n");
    struct task_struct* tasks;
    struct task_struct* child;
    struct list_head* listHead;
    for_each_process(tasks)
    {
        char* isRunning;
        if(tasks->pid > pid)
        {
            if(tasks->state < 0)
            {
                isRunning = "UNRUNNABLE";
            }
            else if(tasks->state > 0)
            {
                isRunning = "STOPPED";
            }
            else
            {
                isRunning = "RUNNABLE";
            }
            printk(KERN_INFO "PROCESS\t%s\t%d\t%s\t%d\t%d\t%d\n", tasks->comm, tasks->pid, isRunning, tasks->prio, tasks->static_prio, tasks->normal_prio);
            if((tasks->parent) != NULL)// I think it needs to be dereferenced to access parent task_struct
            {
                if(tasks->parent->state < 0)
                {
                    isRunning = "UNRUNNABLE";
                }
                else if(tasks->parent->state > 0)
                {
                    isRunning = "STOPPED";
                }
                else
                {
                    isRunning = "RUNNABLE";
                }
                printk(KERN_INFO "PARENT\t%s\t%d\t%s\t%d\t%d\t%d\n", tasks->parent->comm, tasks->parent->pid, isRunning, tasks->parent->prio, tasks->parent->static_prio, tasks->parent->normal_prio);
            }
            //iterate through child list and print info of children
            list_for_each(listHead, &tasks->children)
            {
                child = list_entry(listHead, struct task_struct, sibling);
                if(child->state < 0)
                {
                    isRunning = "UNRUNNABLE";
                }
                else if(child->state > 0)
                {
                    isRunning = "STOPPED";
                }
                else
                {
                    isRunning = "RUNNABLE";
                }
                printk(KERN_INFO "CHILD\t%s\t%d\t%s\t%d\t%d\t%d\n", child->comm, child->pid, isRunning, child->prio, child->static_prio, child->normal_prio);
            }
        }
    }
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

