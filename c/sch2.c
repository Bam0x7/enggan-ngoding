#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

void *thread_function(void *arg) {
    // Mendapatkan informasi penjadwalan untuk thread saat ini
    int policy;
    struct sched_param scheduling_parameters;

    pthread_getschedparam(pthread_self(), &policy, &scheduling_parameters);

    // Menampilkan informasi penjadwalan thread
    printf("Thread ID: %ld, Scheduling Policy: %s, Priority: %d\n",
           (long)pthread_self(),
           (policy == SCHED_FIFO) ? "FIFO" :
           (policy == SCHED_RR) ? "RR" :
           (policy == SCHED_OTHER) ? "OTHER" : "Unknown",
           scheduling_parameters.sched_priority);

    return NULL;
}

int main() {
    // Membuat dua thread
    pthread_t thread1, thread2;

    // Membuat atribut thread untuk menetapkan kebijakan dan prioritas
    pthread_attr_t attr1, attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Menetapkan kebijakan dan prioritas untuk thread pertama (SCHED_FIFO dengan prioritas 50)
    struct sched_param params1;
    params1.sched_priority = 50;
    pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
    pthread_attr_setschedparam(&attr1, &params1);

    // Menetapkan kebijakan dan prioritas untuk thread kedua (SCHED_RR dengan prioritas 40)
    struct sched_param params2;
    params2.sched_priority = 40;
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    pthread_attr_setschedparam(&attr2, &params2);

    // Membuat thread pertama
    if (pthread_create(&thread1, &attr1, thread_function, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Membuat thread kedua
    if (pthread_create(&thread2, &attr2, thread_function, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Menunggu kedua thread selesai
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
