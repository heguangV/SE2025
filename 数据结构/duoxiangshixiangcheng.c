/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  
  
void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
             sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    if ( flag == 1 )  
             {    x = sign * sum;  
                  sum = 0;  
                  flag = 2;  
          sign = 1;  
             }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    return 0;  
}  

void SortPolyn(NODE *P) {
    if (P == NULL || P->next == NULL) {
        return; 
    }
    
    int swapped;
    NODE* ptr1;
    NODE* lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = P;

        while (ptr1->next != lptr) {
            if (ptr1->exp > ptr1->next->exp) {
                int temp_coef = ptr1->coef;
                int temp_exp = ptr1->exp;
                ptr1->coef = ptr1->next->coef;
                ptr1->exp = ptr1->next->exp;
                ptr1->next->coef = temp_coef;
                ptr1->next->exp = temp_exp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void multiplication( NODE * Pa, NODE * Pb , NODE * Pc )  
{  
    NODE* p1 = Pa->next;  
    NODE* p2 = Pb->next;  
    NODE* tail = Pc;    
    
    // 计算所有乘积项
    while (p1 != NULL) {
        p2 = Pb->next; 
        while (p2 != NULL) {
            NODE* new_node = (NODE*)malloc(sizeof(NODE));
            new_node->coef = p1->coef * p2->coef;
            new_node->exp = p1->exp + p2->exp;
            new_node->next = NULL;

            tail->next = new_node;
            tail = new_node;
            
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    
    // 排序：按指数从小到大
    SortPolyn(Pc->next);
    
    // 合并同类项
    NODE* current = Pc->next;
    while(current != NULL && current->next != NULL) {
        if(current->exp == current->next->exp) {
            current->coef += current->next->coef;
            NODE* temp = current->next;
            current->next = current->next->next;
            free(temp);
            // 不移动current，继续检查是否还有相同指数的项
        } else {
            current = current->next;
        }
    }
    
    // 删除系数为0的项
    NODE* prev = Pc;
    current = Pc->next;
    while(current != NULL) {
        if(current->coef == 0) {
            prev->next = current->next;
            NODE* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    // 如果结果为空多项式，添加 <0,0>
    if(Pc->next == NULL) {
        NODE* zero_node = (NODE*)malloc(sizeof(NODE));
        zero_node->coef = 0;
        zero_node->exp = 0;
        zero_node->next = NULL;
        Pc->next = zero_node;
    }
}