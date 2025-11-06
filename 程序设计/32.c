#include<stdio.h>
#include<stdlib.h>
typedef long long ll;

#define MAX_N 500005

int p[MAX_N];
int dp[MAX_N];
ll suf_dp[MAX_N]; // 用于存储 dp 数组的后缀和，防止内层循环

int main(){
    int q;
    scanf("%d", &q);
    
    while(q--){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            scanf("%d", &p[i]);
        }
        dp[0] = 0; // 辅助 dp[0]
        dp[1] = 1;
        for(int i = 2; i <= n; i++){
            int notplus = 0;
            if(p[i] >= p[i-1]){
                notplus++;
            } 
            dp[i] = dp[i-1] - notplus + 1;
        }
        suf_dp[n+1] = 0;
        for(int i = n; i >= 1; i--){
            suf_dp[i] = suf_dp[i+1] + dp[i];
        }
        ll ans = 0; // 从 0 开始累加
        
        for(int i = 1; i <= n; i++){
            ans += suf_dp[i+1]; 
            ans -= (ll)(n - i) * dp[i];
            ans += (ll)(n - i);
        }
        ans += n;

        printf("%lld\n", ans);
    }
    
    return 0;
}