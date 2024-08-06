#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREAD 4
#define ITERATIONS 5

pthread_barrier_t barrier;

void *thread_func(void *arg)
{
    int thread_id = *(int*)arg;

    for(int i=0;i<ITERATIONS;i++){
        printf("thread: %d, iterasi: %d\n" ,thread_id,i);

        int random_delay = rand() % 10000;
        usleep(random_delay);
        pthread_barrier_wait(&barrier);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREAD];
    int thread_id[NUM_THREAD];
    pthread_barrier_init(&barrier,NULL,NUM_THREAD);

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);

    for(int i=0;i<NUM_THREAD;i++){
        thread_id[i] = i;
        if(pthread_create(&thread[i],&thread_attr,thread_func,&thread_id[i])==-1){
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for(int i=0;i<NUM_THREAD;i++){
        if(pthread_join(thread[i],NULL)==-1){
            perror("pthread_join()");
            return EXIT_FAILURE;
        }
    }
    pthread_attr_destroy(&thread_attr);
    pthread_barrier_destroy(&barrier);
    
    return 0;
}
