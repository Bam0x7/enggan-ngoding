#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// Pointer global yang akan dibagikan antar thread
void *shared_ptr;

void *thread_func1(void *arg) {
    // Thread pertama mengalokasikan memori
    shared_ptr = malloc(128);
    if (shared_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        pthread_exit(NULL);
    }
    printf("Thread 1 allocated memory at %p\n", shared_ptr);

    // Mensimulasikan pekerjaan dengan tidur sejenak
    usleep(100);

    // Thread pertama membebaskan memori
    free(shared_ptr);
    printf("Thread 1 freed memory at %p\n", shared_ptr);

    pthread_exit(NULL);
}

void *thread_func2(void *arg) {
    // Mensimulasikan pekerjaan dengan tidur sejenak
    usleep(50);

    // Thread kedua mencoba membebaskan memori yang sama
    free(shared_ptr);
    printf("Thread 2 freed memory at %p\n", shared_ptr);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Membuat thread pertama
    if (pthread_create(&thread1, NULL, thread_func1, NULL)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Membuat thread kedua
    if (pthread_create(&thread2, NULL, thread_func2, NULL)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Menunggu kedua thread selesai
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

