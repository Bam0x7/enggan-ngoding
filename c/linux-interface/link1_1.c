#include <stdio.h>
#include <stdlib.h>

// Struktur untuk node dalam linked list
struct Node {
    int data;
    struct Node* next;
};

// Fungsi untuk menambahkan node baru di awal linked list
void insertAtBeginning(struct Node** head_ref, int new_data) {
    // Membuat node baru
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    // Mengubah head menjadi node baru
    *head_ref = new_node;
}

// Fungsi untuk mencetak isi dari linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Fungsi untuk menghapus node dengan nilai tertentu dari linked list
void deleteNode(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    // Jika node yang akan dihapus adalah node pertama
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    // Mencari node yang akan dihapus
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Jika node tidak ditemukan
    if (temp == NULL) {
        printf("Node with value %d not found\n", key);
        return;
    }

    // Menghubungkan node sebelum dan sesudah node yang akan dihapus
    prev->next = temp->next;
    free(temp);
}

int main() {
    struct Node* head = NULL;

    // Menambahkan node-node baru ke linked list
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 4);
    insertAtBeginning(&head, 5);

    // Mencetak isi dari linked list sebelum penghapusan
    printf("Linked List: ");
    printList(head);

    // Menghapus node dengan nilai 3
    deleteNode(&head, 4);

    // Mencetak isi dari linked list setelah penghapusan
    printf("Linked List after deletion of node with value 3: ");
    printList(head);

    return 0;
}
