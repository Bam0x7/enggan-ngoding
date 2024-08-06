#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    // Mendapatkan kebijakan (policy) penjadwalan saat ini
    int current_policy = sched_getscheduler(0);

    if (current_policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    // Menampilkan kebijakan saat ini
    printf("Current Scheduling Policy: ");
    switch (current_policy) {
        case SCHED_FIFO:
            printf("FIFO (First-In-First-Out)\n");
            break;
        case SCHED_RR:
            printf("RR (Round Robin)\n");
            break;
        case SCHED_OTHER:
            printf("OTHER (Default)\n");
            break;
        default:
            printf("Unknown Policy\n");
    }

    // Mendapatkan informasi penjadwalan untuk proses saat ini
    struct sched_param scheduling_parameters;
    if (sched_getparam(0, &scheduling_parameters) == -1) {
        perror("sched_getparam");
        exit(EXIT_FAILURE);
    }

    // Menampilkan prioritas proses saat ini
    printf("Current Process Priority: %d\n", scheduling_parameters.sched_priority);

    // Mengatur kebijakan dan prioritas proses (contoh: SCHED_FIFO dengan prioritas 50)
    struct sched_param new_parameters;
    new_parameters.sched_priority = 50;

    if (sched_setscheduler(0, SCHED_FIFO, &new_parameters) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    // Menampilkan informasi yang diperbarui
    printf("Updated Scheduling Policy: FIFO\n");
    printf("Updated Process Priority: %d\n", new_parameters.sched_priority);

    return 0;
}
