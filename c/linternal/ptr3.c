#include <stdio.h>
#include <stdlib.h>

void func() {
    system("/bin/sh\x00");
}

int main() {
    unsigned long *ptr = (unsigned long *)malloc(sizeof(unsigned long));
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%p\n", (void *)ptr);
    printf("0x%016lx\n", (unsigned long)ptr);

    *ptr = (unsigned long)0xdeadbeef;

    printf("%p\n", (void *)ptr);
    printf("0x%016lx\n", *ptr);

    free(ptr);

    return 0;
}

