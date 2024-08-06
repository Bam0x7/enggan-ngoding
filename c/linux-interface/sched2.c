#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define errExit(msg)    \
  do {                  \
    perror(msg);        \
    exit(EXIT_FAILURE); \
  } while (0)

int main(int argc, char *argv[]) {
  cpu_set_t set;
  int parentCPU, childCPU, wstatus;
  long nloops;

  if (argc != 4) {
    fprintf(stderr, "Usage: %s parent-cpu child-cpu num-loops\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  parentCPU = strtol(argv[1], NULL, 0);
  childCPU = strtol(argv[2], NULL, 0);
  nloops = strtol(argv[3], NULL, 0);

  CPU_ZERO(&set);

  pid_t c_pid = fork();
  if (c_pid == -1) errExit("fork");

  switch (c_pid) {
    case -1:
      errExit("fork");

    case 0:
      CPU_SET(childCPU, &set);

      if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
        errExit("sched_setaffinity");

      for (int j = 0; j < nloops; j++) getpid();

      exit(EXIT_SUCCESS);

    default:
      CPU_SET(parentCPU, &set);

      if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
        errExit("sched_setaffinity");

      for (int j = 0; j < nloops; j++) getpid();

      if (waitpid(c_pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
        errExit("waitpid");

      exit(EXIT_SUCCESS);
  }
}