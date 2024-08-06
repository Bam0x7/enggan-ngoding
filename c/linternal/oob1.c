#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void oob_example() {
    char buffer[10];
    char *data = "ABCDEFGHIJK";

    // Mengisi buffer dengan data, lebih dari ukuran buffer
    strncpy(buffer, data, 11); // strncpy seharusnya hanya mengisi hingga ukuran buffer

    // Menampilkan isi buffer
    for (int i = 0; i < 12; i++) { // Mengakses 2 byte di luar batas buffer
        printf("buffer[%d] = %c\n", i, buffer[i]);
    }
}

int main() {
    oob_example();
    return 0;
}


