#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int num = 0;

void *add_num() {
  if (num == 0) {
    num += 1;
  }

  return NULL;
}

int main() {
  pthread_t th;

  if (pthread_create(&th, NULL, add_num, NULL) < 0) {
    perror("pthread_create");
    return EXIT_FAILURE;
  }

  if (pthread_join(th, NULL)) {
    perror("pthread_join");
    return EXIT_FAILURE;
  }
  printf("num: %d\n", num);

  return EXIT_FAILURE;
}
