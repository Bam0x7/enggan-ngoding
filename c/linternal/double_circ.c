#include <stdio.h>
#include <stdlib.h>

// Definisi struktur node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Fungsi untuk membuat node baru
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Fungsi untuk mencetak linked list melingkar
void printCircularDoublyList(struct Node* head) {
    if (head == NULL) return;
    struct Node* temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

int main() {
    // Membuat node dan membentuk linked list melingkar ganda
    struct Node* head = createNode(1);
    struct Node* second = createNode(2);
    struct Node* third = createNode(3);

    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;
    third->next = head; // Membentuk lingkaran
    head->prev = third; // Membentuk lingkaran

    // Mencetak linked list melingkar ganda
    printCircularDoublyList(head);

    // Membebaskan memori
    free(third);
    free(second);
    free(head);

    return 0;
}
