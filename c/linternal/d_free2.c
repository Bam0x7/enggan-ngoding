#include <stdio.h>
#include <stdlib.h>

void double_free_example(int condition) {
    char *ptr = (char *)malloc(100);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    printf("Memory allocated at %p\n", ptr);

    // Simulasikan beberapa operasi pada pointer
    ptr[0] = 'A';
    ptr[1] = 'B';

    // Pengkondisian yang menyebabkan free dua kali
    if (condition == 1) {
        free(ptr);
        printf("Memory freed at %p in first condition\n", ptr);
    }

    // Kondisi lain yang juga menyebabkan free
    if (condition == 2 || condition == 1) {
        free(ptr); // Ini akan menyebabkan double-free jika condition == 1
        printf("Memory freed at %p in second condition\n", ptr);
    }
}

int main() {
    int condition = 1; // Ubah nilai ini untuk menguji kondisi yang berbeda

    double_free_example(condition);

    return 0;
}

