#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Node** top, int data) {
    Node* new_node = create_node(data);
    new_node->next = *top;
    *top = new_node;
}

int pop(Node** top) {
    Node* temp = *top;
    int popped_value = temp->data;
    *top = temp->next;
    free(temp);
    return popped_value;
}

int is_empty(Node* top) {
    return top == NULL;
}

void clear_stack(Node** top) {
    while (!is_empty(*top)) {
        pop(top);
    }
}

int main(void) {
    int x=0;
    int n, m;
    scanf("%d%d", &n, &m);
    while (m>0 && n>0) {
        if(x>0) printf("\n");
        for(int round=0; round<m; round++){

        int* seq = (int*)malloc(sizeof(int) * (size_t)n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &seq[i]);
        }

        Node* stack = NULL;
        int next_push = 1;
        int ok = 1;

        for (int i = 0; i < n; i++) {
            int target = seq[i];

            while (next_push <= n && (is_empty(stack) || stack->data != target)) {
                push(&stack, next_push);
                next_push++;
            }

            if (!is_empty(stack) && stack->data == target) {
                (void)pop(&stack);
            } else {
                ok = 0;
                break;
            }
        }

        printf(ok ? "Yes\n" : "No\n");

        clear_stack(&stack);
        free(seq);
    }
    scanf("%d%d", &n, &m);
    x++;
    }

    return 0;
}