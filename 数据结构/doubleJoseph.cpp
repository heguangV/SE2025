#include <stdio.h>  
#include <stdlib.h>  


typedef struct Node {  
    int data;  
    struct Node * next;  
    struct Node * prev;
} Node;  
  
// Initialize a linked list, return its head pointer. Notice that the head node is not effected.  
Node * init_list() {  
    Node * h = (Node *)malloc(sizeof(Node));  
    h->next = NULL;  
    h->data = -1;  
    return h;  
}    

void add_list(Node* h,int n){
    Node* p =h;
    for(int i=1;i<=n;i++){
        Node * b =(Node *)malloc(sizeof(Node));
        b->data = i;
        b->next = NULL;
        b->prev = p;
        p->next = b;
        p = p->next;
    }
    p->next= h->next;
    h->next->prev = p;
}

Node* circle_init(Node* h,int k){
    Node* p = h->next;
    if(k>=1){
        while(p->data!=k){
            p=p->next;
        }
        return p;
    }
}

void circle_list(Node* fir,int m,int n){
	if(m>=1&&n>=1){
		Node* p =fir;
        Node* q = fir;
	    int rem = n; // 使用剩余节点数作为退出条件，避免死循环
	    while(rem > 1){
        	for(int j=1;j<m;j++){
            	p= p->next;
        	}
            for(int j=1;j<m;j++){
            	q= q->prev;
            }
        if(p==q) printf("%d,",p->data);
        else printf("%d-%d,",p->data,q->data);
        if(p==q){
            p->prev->next=p->next;
            q->next->prev = q->prev;
            rem -= 1;
        }
        else{
            p->next->prev=p->prev;
            p->prev->next = p->next;
            q->prev->next=q->next;
            q->next->prev = q->prev;
            rem -= 2;
        }
        p = p->next;
        q = q->prev;
    }
    Node* last = p;
    while (last->next != last) last = last->next;
    if (rem == 1) {
        printf("%d,\n", last->data);
    } else {
        printf("\n");
    }
	}
}

int main(){
    int n=0,k=0,m=0;
    scanf("%d,%d,%d",&n,&k,&m);
    if(k<=0||m<=0||n<=0){
        printf("n,m,k must bigger than 0.\n");
        return 0;
    }
    if(k>n){
        printf("k should not bigger than n.\n");
        return 0;
    }
    Node* head= init_list();
    add_list(head,n);
    Node* fir = circle_init(head,k);
    circle_list(fir,m,n);
    return 0;
}