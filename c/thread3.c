#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ITERATIONS 100000

int shared_variable = 0;
pthread_mutex_t mutex1, mutex2;
pthread_cond_t cond_var1, cond_var2;

void* increment_function1(void* arg) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pthread_mutex_lock(&mutex1);
        shared_variable++;
        printf("fungsi thread 1: %d\n" ,i);
        pthread_mutex_unlock(&mutex1);
    }

    pthread_cond_signal(&cond_var1);

    return NULL;
}

void* increment_function2(void* arg) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pthread_mutex_lock(&mutex2);
        shared_variable++;
        printf("fungsi thread 2: %d\n" ,i);
        pthread_mutex_unlock(&mutex2);
    }

    pthread_cond_signal(&cond_var2);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&cond_var1, NULL);
    pthread_cond_init(&cond_var2, NULL);

    pthread_create(&threads[0], NULL, increment_function1, NULL);
    pthread_create(&threads[1], NULL, increment_function2, NULL);

    pthread_mutex_lock(&mutex1);
    pthread_cond_wait(&cond_var1, &mutex1);
    pthread_mutex_unlock(&mutex1);

    pthread_mutex_lock(&mutex2);
    pthread_cond_wait(&cond_var2, &mutex2);
    pthread_mutex_unlock(&mutex2);

    printf("Nilai akhir dari shared_variable: %d\n", shared_variable);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_cond_destroy(&cond_var1);
    pthread_cond_destroy(&cond_var2);

    return 0;
}
