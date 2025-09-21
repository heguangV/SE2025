#include <stdio.h>
typedef long long ll;

int main(){
    int n=0,q=0;//n 为堆数 q 为次数
    scanf("%d %d",&n,&q);
    int ji=0,ou=0;
    ll amount=0;
    for(int i=0;i<n;i++){
        int x =0;
        scanf("%d",&x);
        if(x%2==0) ou++;
        else ji++;
        amount += x;
    }
    for(int i=0;i<q;i++){
        int x=0,y=0;//x wei biaozhi ,y daibiao shiliang
        scanf("%d %d",&x,&y);
        if(y%2==1) {
            if(x==1) {
                amount += ji*y;
                ou += ji;
                ji = 0;
            }
            else {
                amount += ou*y;
                ji += ou;
                ou = 0;
            }
        }
        else {
            if(x==1) {
                amount += ji*y;
            }
            else {
                amount += ou*y;
            }
        }
    }   
    printf("%d\n",amount);
    return 0;
}