#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listnode
{
    int num;
    char str[20];
    struct listnode *next;
}ListNode;

ListNode * init_list() {  
    ListNode * h = (ListNode *)malloc(sizeof(ListNode));  
    h->next = NULL;  
    h->num = -1;  
    return h;  
}    

void add_list(ListNode* h,int num,char* str){
    ListNode* p =h;
    ListNode * b =(ListNode *)malloc(sizeof(ListNode));
    while(p->next!=NULL){
        p=p->next;
    }
    b->num = num;
    strcpy(b->str,str);
    b->next = NULL;
    p->next = b;

}

int main(){
    int n,m;
    scanf("%d",&n);
    ListNode* head1 = init_list();
    ListNode* head2 = init_list();
    for(int i=0;i<n;i++){
        int num;
        char str[20];
        scanf("%d %s",&num,str);
        add_list(head1,num,str);
    }
    scanf("%d",&m);
    if(m==0){
        printf("the LIST2 is NULL.\n");
        return 0;
    }
    for(int i=0;i<m;i++){
        int num;
        char str[20];
        scanf("%d %s",&num,str);
        add_list(head2,num,str);
    }
    int cnt=0;
    for(ListNode* p=head2->next;p!=NULL;p=p->next){
        int flag = 1;
        for(ListNode* q=head1->next;q!=NULL;q=q->next){
            if(p->num==q->num && strcmp(p->str,q->str)==0){
                flag=0;
                break;
            }
        }
        if(flag){
            printf("%d %s is not in LIST1.\n", p->num, p->str);
            cnt=1;
        }
    }
    if(cnt==0){
        printf("the records of LIST2 are all in the LIST1.\n");
    }
    return 0;
}
