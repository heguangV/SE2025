#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
void output( NODE * );  
void change( int, int, NODE * );  
  
void output( NODE * head )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<50 )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");  
}  
  
int main()  
{   int n, m;  
    NODE * head;  
  
    scanf("%d%d", &n, &m);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head );  
    return 0;  
}

void change( int n, int m, NODE * head )  
{   
    if (m == 0) return;             
    if (m < 0) { n = -n; m = -m; }   
    int r = n % m; 
    if (r < 0) r += m;                
    NODE *p = head;
    int cnt = 0;
    while (r != 0 && cnt < 50)  
    {
        r *= 10;
        int digit = r / m;
        r = r % m;

        NODE *q = (NODE*)malloc(sizeof(NODE));
        if (!q) break;
        q->data = digit;
        q->next = NULL;
        p->next = q;
        p = q;

        cnt++;
    }
}