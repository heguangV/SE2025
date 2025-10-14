#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int xishu;
    int zhishu;
    struct Node* next;
}Node;

typedef Node* polynomial;
polynomial Pa, Pb, Pc;

void SortPolyn(polynomial *P) {
    if (*P == NULL || (*P)->next == NULL) {
        return; 
    }
    
    int swapped;
    polynomial ptr1;
    polynomial lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = *P;
        
        while (ptr1->next != lptr) {
            if (ptr1->zhishu > ptr1->next->zhishu) {
                int temp_xishu = ptr1->xishu;
                int temp_zhishu = ptr1->zhishu;
                ptr1->xishu = ptr1->next->xishu;
                ptr1->zhishu = ptr1->next->zhishu;
                ptr1->next->xishu = temp_xishu;
                ptr1->next->zhishu = temp_zhishu;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void CreatePolyn(polynomial *P, int m) {
    *P = NULL;
    polynomial tail = NULL;
    for (int i = 0; i < m; i++) {
        int x, z;
        scanf("%d %d", &x, &z);
        
        polynomial new_node = (polynomial)malloc(sizeof(Node));
        new_node->xishu = x;
        new_node->zhishu = z;
        new_node->next = NULL;
        
        if (*P == NULL) {
            *P = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
}

void AddPolyn(polynomial *Pa, polynomial Pb) {
    polynomial p1 = *Pa;
    polynomial p2 = Pb;
    polynomial new_head = NULL;
    polynomial tail = NULL;

    while (p1 != NULL && p2 != NULL) {
        polynomial new_node = (polynomial)malloc(sizeof(Node));
        if (p1->zhishu == p2->zhishu) {
            new_node->xishu = p1->xishu + p2->xishu;
            new_node->zhishu = p1->zhishu;
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->zhishu > p2->zhishu) {
            new_node->xishu = p1->xishu;
            new_node->zhishu = p1->zhishu;
            p1 = p1->next;
        } else {
            new_node->xishu = p2->xishu;
            new_node->zhishu = p2->zhishu;
            p2 = p2->next;
        }
        new_node->next = NULL;

        if (tail == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    while (p1 != NULL) {
        polynomial new_node = (polynomial)malloc(sizeof(Node));
        new_node->xishu = p1->xishu;
        new_node->zhishu = p1->zhishu;
        new_node->next = NULL;

        if (tail == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        p1 = p1->next;
    }

    while (p2 != NULL) {
        polynomial new_node = (polynomial)malloc(sizeof(Node));
        new_node->xishu = p2->xishu;
        new_node->zhishu = p2->zhishu;
        new_node->next = NULL;

        if (tail == NULL) {
            new_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        p2 = p2->next;
    }
    
    polynomial temp;
    while (*Pa != NULL) {
        temp = *Pa;
        *Pa = (*Pa)->next;
        free(temp);
    }
    
    *Pa = new_head;
    
    // 排序：按指数从小到大
    SortPolyn(Pa);
}

void PrintPolyn(polynomial P) {
    polynomial p = P;
    int first = 1; // 标记是否是第一项
    
    
    while (p != NULL) {
        if (p->xishu != 0) {
            if (!first) {
                printf(",");
            }
            printf("<%d,%d>", p->xishu, p->zhishu);
            first = 0;
        }
        p = p->next;
    }
    
    // 如果所有项都被过滤（系数都是0），输出<0,0>
    if (first) {
        printf("<0,0>");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    if(T==1){
        int m1,m2,m3;
        scanf("%d", &m1);
        CreatePolyn(&Pa, m1);
        scanf("%d", &m2);
        CreatePolyn(&Pb, m2);
        scanf("%d", &m3);
        CreatePolyn(&Pc, m3);
        PrintPolyn(Pa);
        printf("\n");
        PrintPolyn(Pb);
        printf("\n");
        PrintPolyn(Pc);
        printf("\n");
        AddPolyn(&Pa, Pb);
        PrintPolyn(Pa);
        printf("\n");
        AddPolyn(&Pa, Pc);
        PrintPolyn(Pa);
        printf("\n");
    }
    return 0;
}