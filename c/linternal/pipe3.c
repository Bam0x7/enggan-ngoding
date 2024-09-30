#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

// Fungsi yang akan dijalankan oleh thread
void *compute_task(void *arg) {
    // Mendapatkan PID (Process ID) dari thread saat ini
    pid_t pid = getpid();
    
    // Menetapkan afinitas CPU untuk thread saat ini
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET((int)arg, &cpuset);
    if (sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    // Melakukan komputasi
    for (int i = 0; i < 1000000000; ++i) {
        // Do some computation
    }

    printf("Thread %ld has affinity set to CPU %d.\n", (long)arg, (int)arg);

    return NULL;
}

int main() {
    // Mendapatkan jumlah CPU yang tersedia
    int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPUs: %d\n", num_cpus);

    // Menetapkan afinitas CPU untuk thread utama (proses)
    cpu_set_t main_cpuset;
    CPU_ZERO(&main_cpuset);
    CPU_SET(0, &main_cpuset);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &main_cpuset) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    // Membuat thread untuk setiap CPU
    pthread_t threads[num_cpus];
    for(long i = 1; i < num_cpus; ++i) {
        if (pthread_create(&threads[i], NULL, compute_task, (void *)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Menunggu semua thread selesai
    for (long i = 1; i < num_cpus; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have completed.\n");

    return 0;
}
