#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int i;

    // Akses di luar batas array
    for (i = 0; i <= 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}

