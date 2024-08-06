#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr;

    // Assign alamat array arr ke pointer ptr
    ptr = arr;

    // Mengubah nilai indeks ke-2 dari array arr menjadi 10 menggunakan pointer
    *(ptr + 1) = 10;

    // Menampilkan nilai array arr setelah diubah
    printf("Nilai array arr setelah diubah:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(arr+i));
    }
    printf("\n");

    return 0;
}
