#include <stdio.h>

// Makro untuk mencari elemen dalam array
#define FIND_ELEMENT(array, length, element) ({ \
    int index = -1;                             \
    for (int i = 0; i < (length); ++i) {        \
        if ((array)[i] == (element)) {          \
            index = i;                          \
            break;                              \
        }                                       \
    }                                           \
    index;                                      \
})

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(arr) / sizeof(arr[0]);
    int element_to_find = 7;

    // Menggunakan makro untuk mencari elemen dalam array
    int index = FIND_ELEMENT(arr, length, element_to_find);

    if (index != -1) {
        printf("Element %d found at index %d\n", element_to_find, index);
    } else {
        printf("Element %d not found in the array\n", element_to_find);
    }

    return 0;
}

