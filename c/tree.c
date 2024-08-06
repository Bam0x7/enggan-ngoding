#include <stdio.h>
#include <stdlib.h>

// Struktur untuk merepresentasikan simpul dalam binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Fungsi untuk membuat simpul baru
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Fungsi untuk menyisipkan elemen ke dalam binary tree
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Fungsi untuk mencetak elemen-elemen dalam binary tree secara inorder
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);        
        postorderTraversal(root->left);
        postorderTraversal(root->right);
    }
}

void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        preorderTraversal(root->left);        
        preorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;

    // Menyisipkan elemen ke dalam binary tree
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);

    // Mencetak elemen-elemen dalam binary tree
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
