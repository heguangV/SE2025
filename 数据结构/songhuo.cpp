#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;     // 存储货物
    int front;      // 队首
    int rear;       // 队尾
    int size;       // 当前大小
    int capacity;   // 容量
} Queue;

typedef struct {
    int *items;     // 存储货物
    int top;        // 栈顶
    int capacity;   // 容量
} Stack;

void initQueue(Queue *q, int capacity) {
    q->capacity = capacity > 0 ? capacity : 1;
    q->items = (int*)malloc(sizeof(int) * q->capacity);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

void freeQueue(Queue *q) {
    if (q->items) free(q->items);
    q->items = NULL;
    q->capacity = q->front = q->rear = q->size = 0;
}

int isQueueEmpty(Queue *q) {
    return q->size == 0;
}

int isQueueFull(Queue *q, int limit) {
    return q->size >= limit;
}

void enqueue(Queue *q, int item) {
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

int dequeue(Queue *q) {
    int item = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

void initStack(Stack *s, int capacity) {
    s->capacity = capacity > 0 ? capacity : 1;
    s->items = (int*)malloc(sizeof(int) * s->capacity);
    s->top = 0;
}

void freeStack(Stack *s) {
    if (s->items) free(s->items);
    s->items = NULL;
    s->capacity = s->top = 0;
}

int isStackEmpty(Stack *s) {
    return s->top == 0;
}

int isStackFull(Stack *s) {
    return s->top >= s->capacity;
}

void push(Stack *s, int item) {
    s->items[s->top++] = item;
}

int pop(Stack *s) {
    return s->items[--s->top];
}

int peek(Stack *s) {
    return s->items[s->top - 1];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, S, Q;
        scanf("%d%d%d", &N, &S, &Q);
        Queue *stations = (Queue*)malloc(sizeof(Queue) * (N + 1));
        for (int i = 1; i <= N; i++) {
            initQueue(&stations[i], Q > 0 ? Q : 1);
        }
        
        for (int i = 1; i <= N; i++) {
            int m;
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                int target;
                scanf("%d", &target);
                enqueue(&stations[i], target);
            }
        }
        Stack carrier;
        initStack(&carrier, S > 0 ? S : 1);
        long long time = 0;
        int currentStation = 1;
        int finished = 0;
        while (!finished) {
            while (!isStackEmpty(&carrier)) {
                int target = peek(&carrier);
                if (target == currentStation) {
                    pop(&carrier);
                    time++;
                } else if (!isQueueFull(&stations[currentStation], Q)) {
                    enqueue(&stations[currentStation], pop(&carrier));
                    time++;
                } else {
                    break;
                }
            }
            while (!isStackFull(&carrier) && !isQueueEmpty(&stations[currentStation])) {
                push(&carrier, dequeue(&stations[currentStation]));
                time++;
            }
            if (isStackEmpty(&carrier)) {
                finished = 1;
                for (int i = 1; i <= N; i++) {
                    if (!isQueueEmpty(&stations[i])) {
                        finished = 0;
                        break;
                    }
                }
                if (finished) {
                    printf("%lld\n", time);
                    break;
                }
            }
            currentStation = (currentStation % N) + 1;
            time += 2;
        }
        for (int i = 1; i <= N; i++) {
            freeQueue(&stations[i]);
        }
        free(stations);
        freeStack(&carrier);
    }
    
    return 0;
}