#include <stdio.h>  
#include <stdlib.h>  


typedef struct Node {  
    int data;  
    struct Node * next;  
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
        p->next = b;
        p = p->next;
    }
    p->next= h->next;
}

Node* circle_init(Node* h,int k){
    Node* p = h->next;
    if(k>=1){
        while(p->next->data!=k){
            p=p->next;
        }
        return p;
    }
    else{
        printf("n,m,k must bigger than 0.\n");
    }
}

void circle_list(Node* fir,int m,int n){
	int i =0;
	if(m>=1&&n>=1){
		Node* p =fir;
    	while(p->next!=p){
        	for(int j=1;j<m;j++){
            	p= p->next;
        	}
        i++;
        printf("%d",p->next->data);
        if(i%10==0) printf("\n");
        else printf(" ");
        p->next=p->next->next;
    }
    printf("%d\n",p->data);
	}
    else{
        printf("n,m,k must bigger than 0.\n");
    }
}

int main(){
    int n=0,k=0,m=0;
    scanf("%d,%d,%d",&n,&k,&m);
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