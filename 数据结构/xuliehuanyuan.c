#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// 二叉树节点结构
typedef struct Node {
    char data;
    struct Node* son[2];  // son[0]左子树, son[1]右子树
} Node;

// 二叉树结构
typedef struct BiTree {
    Node* root;
    int n;
} BiTree;

// 队列结构用于层序遍历
typedef struct Queue {
    Node* data[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 队列操作
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    q->data[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->data[q->front++];
}

// 在中序序列中查找字符位置
int findChar(const char* str, char target, int start, int end) {
    for (int i = start; i < end; i++) {
        if (str[i] == target) {
            return i;
        }
    }
    return end;  // 未找到
}

// 构建二叉树
void buildTree(Node** rt, const char* postOrdered, const char* inOrdered, 
               int l, int r, int* d) {
    if (l >= r) {
        return;
    }
    
    int index = findChar(inOrdered, postOrdered[*d - 1], l, r);
    if (index == r) {
        return;
    }
    
    *rt = (Node*)malloc(sizeof(Node));
    (*rt)->data = postOrdered[--(*d)];
    (*rt)->son[0] = NULL;
    (*rt)->son[1] = NULL;
    
    // 先构建右子树，再构建左子树
    buildTree(&((*rt)->son[1]), postOrdered, inOrdered, index + 1, r, d);
    buildTree(&((*rt)->son[0]), postOrdered, inOrdered, l, index, d);
}

// 层序遍历
void levelOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    while (!isQueueEmpty(&q)) {
        Node* t = dequeue(&q);
        printf("%c", t->data);
        
        for (int i = 0; i < 2; i++) {
            if (t->son[i] != NULL) {
                enqueue(&q, t->son[i]);
            }
        }
    }
    printf("\n");
}

// 释放二叉树内存
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    
    for (int i = 0; i < 2; i++) {
        freeTree(root->son[i]);
    }
    free(root);
}

// 创建二叉树
BiTree* createBiTree(const char* postOrdered, const char* inOrdered) {
    BiTree* tree = (BiTree*)malloc(sizeof(BiTree));
    tree->n = strlen(postOrdered);
    
    int d = tree->n;  // 从后序遍历的最后一个字符开始
    tree->root = NULL;
    buildTree(&(tree->root), postOrdered, inOrdered, 0, tree->n, &d);
    
    return tree;
}

int main() {
    char in[MAX_SIZE], post[MAX_SIZE];
    
    // 读取输入
    scanf("%s", in);
    scanf("%s", post);
    
    // 创建二叉树
    BiTree* tree = createBiTree(post, in);
    
    // 层序遍历输出
    levelOrder(tree->root);
    
    // 释放内存
    freeTree(tree->root);
    free(tree);
    
    return 0;
}