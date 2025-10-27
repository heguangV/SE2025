#include<stdio.h>
#include<stdlib.h>

int *dp,*bridge;

int main(){
    int l;
    scanf("%d",&l);
    int s,t,m;
    scanf("%d%d%d",&s,&t,&m);
        dp = (int *)malloc((l+1+t)*sizeof(int));
    bridge = (int *)malloc((l+t+1)*sizeof(int));
    for(int i=0;i<=l+t;i++){
        dp[i] = 101;
        bridge[i] = 0;
    }
    for(int i=0;i<m;i++){
        int pos;
        scanf("%d",&pos);
        bridge[pos] = 1;
    }
    dp[0] = 0;
    for(int i=s;i<=l+t;i++){
        for(int j =s;j<=t;j++){
            if(dp[i-j]+bridge[i]<dp[i]&&i-j>=0&&i-j<=l){
                dp[i] = dp[i-j]+bridge[i];
            }
        }
    }
    int ans = 101;
    for(int i=l;i<=l+t;i++){
        if(dp[i]<ans){
            ans = dp[i];
        }
    }
    printf("%d\n",ans);
    free(dp);
    free(bridge);
    return 0;
}