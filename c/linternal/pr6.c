#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
  int pid;
  pid = fork();
 
  if (pid == 0)
  {
    printf ("Child : I am the child process\n");
    printf ("Child : Child’s PID: %d\n", getpid());
    printf ("Child : Parent’s PID: %d\n", getppid());
  }
  else
  {
    printf ("Parent : I am the parent process\n");
    printf ("Parent : Parent’s PID: %d\n", getpid());
    printf ("Parent : Child’s PID: %d\n", pid);
  }
}