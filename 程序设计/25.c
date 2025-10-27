#include<stdio.h>
#include<stdlib.h>
typedef struct Stock{
    int price, profit;
} stock;
int * dp;

int qsort_cmp(const void *a, const void *b) {
    stock *sa = (stock *)a;
    stock *sb = (stock *)b;
    return sb->price - sa->price;
}
int main(){
    int s,n,d;
    scanf("%d%d%d",&s,&n,&d);//s:总钱数 n:购买次数 d:债券数
    stock *stocks = (stock *)malloc(d * sizeof(stock));
    for(int i=0;i<d;i++){
        scanf("%d%d",&stocks[i].price,&stocks[i].profit);
    }
    qsort(stocks,d,sizeof(stock),qsort_cmp);// 降序排列
    int min_price=stocks[d-1].price/1000;
    int ans=s;
    for(int i=0;i<n;i++){
        int dp[s/1000+1];
        for(int j=0;j<=s/1000;j++){
            dp[j] = 0;
        }
        for(int j=0;j<d;j++){
            int price_thousand = stocks[j].price / 1000;
            int profit_thousand = stocks[j].profit ;
            for(int k=price_thousand;k<=s/1000;k++){
                if(dp[k - price_thousand] + profit_thousand > dp[k]){
                    dp[k] = dp[k - price_thousand] + profit_thousand;
                }
            }
        }
        ans += dp[s/1000];
        s = ans;
    }
    free(stocks);
    printf("%d\n",ans);
    return 0;
}