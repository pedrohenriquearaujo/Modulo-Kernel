#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/init_task.h>

void DFS(struct task_struct *task)
{   
    struct task_struct *child;
    struct list_head *list;

    printk("name: %s, pid: [%d], state: %li, Pai do processo: %i\n", task->comm, task->pid, task->state, task->parent->pid);
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        DFS(child);
    }
}



void procs_info_print(void)
{
        struct task_struct* task_list;
        size_t process_counter = 0;
        
        for_each_process(task_list) {
                pr_info("== %s [%d]\n", task_list->comm, task_list->pid);
                ++process_counter;
        }
        printk(KERN_INFO "== Number of process: %zu\n", process_counter);
}

int init_module(void)
{
        printk(KERN_INFO "[ INIT ==\n");

        procs_info_print();
        DFS(&init_task);

        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "== CLEANUP ]\n");
}

MODULE_LICENSE("GLP");