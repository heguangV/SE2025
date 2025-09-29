#include"stdio.h"

typedef long long ll;

int main(){
    int T;
    scanf("%d",&T);
    for(int i=0;i<T;i++){
        ll a,b,c,d;    
        int count=0;
        scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
        ll cnt = c*d;
        for(ll y=1;y*b<cnt;y++){
        if((a*c*y)%(c*d-b*y)==0&&(c*d-b*y)>0){
                count++;
            }
        }
        printf("%d\n",count);
    }
    return 0;
}
