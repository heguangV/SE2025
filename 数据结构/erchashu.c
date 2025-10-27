#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 标准二叉链表节点
typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

// 函数声明
Node* build_tree_from_level_order(const char* str);
void show_tree(Node* root, int depth);
void preorder(Node* root);
void inorder(Node* root);
void postorder(Node* root);
int count_leafs(Node* root);
void swap_tree(Node* root);
void free_tree(Node* root);

int main() {
    char input[1000];
    scanf("%s", input);

    Node* root = build_tree_from_level_order(input);

    printf("BiTree\n");
    show_tree(root, 0);

    printf("pre_sequence  : ");
    preorder(root);
    printf("\n");

    printf("in_sequence   : ");
    inorder(root);
    printf("\n");

    printf("post_sequence : ");
    postorder(root);
    printf("\n");

    int leaf_count = count_leafs(root);
    printf("Number of leaf: %d\n", leaf_count);

    swap_tree(root);

    printf("BiTree swapped\n");
    show_tree(root, 0);

    printf("pre_sequence  : ");
    preorder(root);
    printf("\n");

    printf("in_sequence   : ");
    inorder(root);
    printf("\n");

    printf("post_sequence : ");
    postorder(root);
    printf("\n");

    free_tree(root);

    return 0;
}

// 只将'#'视为空节点
Node* build_tree_from_level_order(const char* str) {
    if (str == NULL || str[0] == '#' || str[0] == '\0') {
        return NULL;
    }

    // 队列现在可以存储 NULL 指针
    Node** queue = (Node**)malloc(strlen(str) * sizeof(Node*));
    int front = 0, rear = 0;
    int i = 0; // 字符串索引

    // 创建根节点
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = str[i++];
    root->left = root->right = NULL;
    queue[rear++] = root;

    while (front < rear && i < strlen(str)) {
        Node* current = queue[front++];

        // 如果从队列中取出的是 NULL，说明这是一个空位
        // 它没有子节点可以连接，但它在输入字符串中占了两个子节点的位置
        if (current == NULL) {
            i += 2; // 跳过它的两个虚构的子节点
            continue;
        }

        // 处理左孩子
        if (i < strlen(str)) {
            if (str[i] != '#') {
                Node* left_child = (Node*)malloc(sizeof(Node));
                left_child->data = str[i];
                left_child->left = left_child->right = NULL;
                current->left = left_child;
                queue[rear++] = left_child; // 有效节点入队
            } else {
                queue[rear++] = NULL; // 空节点标记(NULL)入队
            }
            i++;
        }

        // 处理右孩子
        if (i < strlen(str)) {
            if (str[i] != '#') {
                Node* right_child = (Node*)malloc(sizeof(Node));
                right_child->data = str[i];
                right_child->left = right_child->right = NULL;
                current->right = right_child;
                queue[rear++] = right_child; // 有效节点入队
            } else {
                queue[rear++] = NULL; // 空节点标记(NULL)入队
            }
            i++;
        }
    }

    free(queue);
    return root;
}

void show_tree(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < depth * 4; i++) {
        printf(" ");
    }
    printf("%c\n", root->data);
    show_tree(root->left, depth + 1);
    show_tree(root->right, depth + 1);
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

int count_leafs(Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return count_leafs(root->left) + count_leafs(root->right);
}

void swap_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    swap_tree(root->left);
    swap_tree(root->right);
}

void free_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}