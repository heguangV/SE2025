#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
    int height; // 节点高度
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

void updateHeight(Node* node) {
    if (node == NULL) return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

int getBalance(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// 插入节点并保持平衡（递归方式）
Node* insert(Node* node, char key) {
    // 1. 普通BST插入
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node; // 重复值不插入

    // 2. 更新高度
    updateHeight(node);

    // 3. 获取平衡因子
    int balance = getBalance(node);

    // 4. 不平衡情况处理

    // LL
    if (balance > 1 && key < node->left->data)
        return rotateRight(node);

    // RR
    if (balance < -1 && key > node->right->data)
        return rotateLeft(node);

    // LR
    if (balance > 1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // RL
    if (balance < -1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// 按输入顺序建立 AVL 树
Node* build_avl_from_input_order(const char* str) {
    Node* root = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        root = insert(root, str[i]);
    }
    return root;
}

// 你的遍历和打印函数保持不变
void show_tree(Node* root, int depth) {
    if (root == NULL) return;
    show_tree(root->right, depth + 1);
    for (int i = 0; i < depth * 4; i++) printf(" ");
    printf("%c\n", root->data);
    show_tree(root->left, depth + 1);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

int main() {
    char input[1000];
    scanf("%s", input);

    Node* root = build_avl_from_input_order(input);

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");
    printf("Tree:\n");
    show_tree(root, 0);
    return 0;
}

