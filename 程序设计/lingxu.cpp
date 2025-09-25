#include<stdio.h> 
#include<math.h> 
 
typedef long long ll; 
 
int main(){ 
    int T; 
    scanf("%d",&T); 
    for(int i=0;i<T;i++){ 
        ll n,m; 
        scanf("%lld %lld",&n,&m); 
        ll cnt = 1 << m;
        int ans=0; 
        int f[200][200]={0};//qianyige jilu guaxiang  houyige jilu yihuojieguo
        for(ll i=0;i<cnt;i++){//chushihua guaxiang lujing
            f[i][i]=1;
        } 
        int newf[200][200]={0};// linshi lujing
        for (ll i = 2; i < n; i++) {// cong2kaishi zai f jichushang//xianbukaolv n
            for (ll end = 0; end < cnt; end++) {// xulie zuihouyige
                for(ll sum = 0; sum < cnt; sum++) {// dngqian yihuohe
                    if(f[end][sum]==0) continue; //tiaoguo meiyou lujing de
                    for (ll k=0;k<cnt;k++){// tianjiaxilie xiayixiang
                        if(k==end) continue;// tiaoguo xiangtong de
                        newf[k][sum^k]+=f[end][sum];// jia shang xiangtong de
                    }
                }
            }
            for(ll end=0;end<cnt;end++){ 
                for(ll sum=0;sum<cnt;sum++){ 
                    f[end][sum]=newf[end][sum]; 
                    newf[end][sum]=0; 
                }
            }
        }
        for(ll end=0;end<cnt;end++){ 
            for(ll sum=0;sum<cnt;sum++){ 
                if(sum!=end) ans+=f[end][sum];
            } 
        }
    printf("%d\n",ans); 
    } 
    return 0; 
}  