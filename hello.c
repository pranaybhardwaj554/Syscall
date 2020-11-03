/* Name: Pranay Bhardwaj
   Roll_Number: 2019263 */
#include <sys/dir.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
int pid;
char file[256];
int main(int argc, char const *argv[])
{
	printf("Enter the pid: ");
	scanf("%d",&pid);
	printf("Enter the File name: ");
	scanf("%s",file);
	int see=syscall(548,pid,file);
	//if syscall encounters an error;
	if(see<0){
		printf("Error number is: %d\n",errno );
		perror("Error encountered");
	}
	printf("Syscall sys_sh_task_info returned %d \n",see);
	return 0;
}
