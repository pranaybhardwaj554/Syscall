#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>  
#include <linux/kernel.h> 
#include <linux/fs.h>    
#include <linux/fcntl.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <linux/buffer_head.h>
#include <asm/segment.h>

SYSCALL_DEFINE2(sh_task_info, int, pid, char __user*, path) {
   	int hell=0;
   	int fd=0;
   	int len=250;
   	char buf[256];
   	unsigned long lenleft = len;
    struct file *f;
    unsigned long chunklen = sizeof(buf);        
    while( lenleft > 0 ){
        if( lenleft < chunklen ) chunklen = lenleft;
            if( copy_from_user(buf, path, chunklen) ){
	    		return -EFAULT;
    	}
            lenleft -= chunklen;
        }
    char tobeprinted[256]="";
	char nprio[50]="";
	char lid[50]="";
	char state[50]="";
	char prio[50]="";
	char rtprio[50]="";
	char sprio[50]="";
	//int fd;
	struct task_struct *current_process;
        struct file *file;
        for_each_process(current_process){
        	if(pid == (int)current_process->pid){
        		printk("Yes the process is found");
        		strncat(tobeprinted,"Process: ",9);
        		strcat(tobeprinted,current_process->comm);
        		strcat(tobeprinted,"\n");
        		printk("Process: %s\n",current_process->comm); 
				strncat(tobeprinted,"PID_Number: ",12);
				sprintf(lid,"%ld",(long)task_pid_nr(current_process)); 
        		strncat(tobeprinted,lid,strlen(lid));
        		strcat(tobeprinted,"\n");
				printk("PID_Number: %ld\n",(long)task_pid_nr(current_process));
				strncat(tobeprinted,"Process State: ",15);
				sprintf(state,"%ld",(long)(current_process->state)); 
        		strncat(tobeprinted,state,strlen(state));
        		strcat(tobeprinted,"\n");
				printk("Process State: %ld\n",(long)current_process->state );
				strncat(tobeprinted,"Priority: ",10);
				sprintf(prio,"%ld",(long)(current_process->prio)); 
        		strncat(tobeprinted,prio,strlen(prio));
        		strcat(tobeprinted,"\n");
				printk("Priority: %ld\n",(long)current_process->prio);
				strncat(tobeprinted,"RT_Priority: ",13);
				sprintf(rtprio,"%ld",(long)(current_process->rt_priority)); 
        		strncat(tobeprinted,rtprio,strlen(rtprio));
        		strcat(tobeprinted,"\n");
				printk("RT_Priority: %ld\n",(long)current_process->rt_priority);
				strncat(tobeprinted,"Static Priority: ",16);
				sprintf(sprio,"%ld",(long)(current_process->static_prio)); 
        		strncat(tobeprinted,sprio,strlen(sprio));
        		strcat(tobeprinted,"\n");
				printk("Static Priority: %ld\n",(long)current_process->static_prio);
				strncat(tobeprinted,"Normal Priority: ",17);
				sprintf(nprio,"%ld",(long)(current_process->normal_prio)); 
        		strncat(tobeprinted,nprio,strlen(nprio));
        		strcat(tobeprinted,"\n");
        		strcat(tobeprinted,"\0");
        		strcat(tobeprinted,"\0");
        		strcat(tobeprinted,"\n");
        		strcat(tobeprinted,"\n");
        		hell=1;
        		printk("Normal Priority: %ld\n",(long)current_process->normal_prio); 
			}	
        }
    if(hell==0){
    	return -ESRCH;
    }    
    file = filp_open(buf, O_WRONLY | O_CREAT, 0644);
  	if(IS_ERR(file)) {
   		return PTR_ERR(file);
  	 }
 	 fd = kernel_write(file, tobeprinted, strlen(tobeprinted), 0);
 	 filp_close(file, 0);
	 return 0;
}