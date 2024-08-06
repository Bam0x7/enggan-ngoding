#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ptrace.h>

int main(int arg, char *argv[])
{
	int pid;
	int syscall_no;

	if((pid = fork()) == 0){
		ptrace(PTRACE_TRACEME,0,NULL,NULL);
		execl("/bin/ls","ls",NULL);
	}else{
		wait(NULL);
		syscall_no = ptrace(PTRACE_SYSCALL,pid,0,0);
		printf("child made system call no: %d\n" ,syscall_no);
		ptrace(PTRACE_CONT,pid,NULL,NULL);
	}

	return EXIT_SUCCESS;
}
