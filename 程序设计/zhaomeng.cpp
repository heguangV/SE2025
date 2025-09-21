#include<stdio.h>

const int maxn = 1005;  
int n;  
bool good[maxn][maxn];  
void guessdalao(int n); // you should finish this  
int better(int a, int b)  
{  
    if (a <= 0 || a > n || b <= 0 || b > n) return -1;  
    return good[a][b];  
}  
int main()  
{  
    scanf("%d", &n);  
    for (int i = 1; i <= n; i++)  
        for (int j = 1; j <= n; j++)  
        {  
            int t;  
            scanf("%d", &t);  
            good[i][j] = t;  
        }  
    guessdalao(n);  
    return 0;  
}  
 
void guessdalao(int n) 
{ 
    int can=1;
    for(int i=1;i<=n;i++){
        if(better(can,i)==0) can=i;
    }
    for (int i = 1; i <= n; i++)
    {
        if(i!=can && (better(i,can) || better(can,i)== 0)){
            printf("-1\n");
            return;
        }
    }
    printf("%d\n", can);
} 