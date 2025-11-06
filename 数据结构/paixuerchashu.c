#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf(" %d", root->data);
    inorder(root->right);
}

void show_tree(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    show_tree(root->left, depth + 1);
    for (int i = 0; i < depth * 4; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    show_tree(root->right, depth + 1);
}

void search(Node* root, int key) {
    Node* current = root;
    while (current != NULL) {
        if (current->data < key) {
            if(current->right == NULL){
                Node* right_child = (Node*)malloc(sizeof(Node));
                right_child->data = key;
                right_child->left = right_child->right = NULL;
                current->right = right_child;
                return;
            }
            current = current->right;
        }
        if (key < current->data) {
            if(current->left == NULL){
                Node* left_child = (Node*)malloc(sizeof(Node));
                left_child->data = key;
                left_child->left = left_child->right = NULL;
                current->left = left_child;
                return;
            }
            current = current->left;
        }
    }
    return;            
}
  
Node* build_tree_from_level_order(int* arr, int n) {
    if (n == 0) return NULL;
    int i = 0;
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = arr[i++];
    root->left = root->right = NULL;

    for(int j = 1; j < n; j++){
        search(root, arr[j]);
    }
    return root;
}

int main() {
    int arr[1000];
    int i = 0, n;
    while (1) {
        scanf("%d", &arr[i]);
        if (arr[i] == 0) {
            n = i;
            break;
        }
        i++;
    }
    Node* root = build_tree_from_level_order(arr, n);
    show_tree(root, 0);
    printf("\n");
    inorder(root);
    printf("\n");
    return 0;
}