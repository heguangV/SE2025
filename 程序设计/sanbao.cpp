#include<stdio.h>
#include<stdlib.h>
#define N 1000000  
#define MaxNum 1000000000  
  
int S1[N],S2[N],S3[N];  
  
int DiffWeight(int i, int j, int k){  
    return abs(S1[i] - S2[j]) + abs(S2[j] - S3[k]) + abs(S3[k] - S1[i]);  
}  
// 返回S1[i],S2[j],S3[k]中最小的序号  
// 返回i表示Si对应的数最小  
int xls_min(int i, int j, int k){  
    if(S1[i] <= S2[j]){  
        if(S1[i] <= S3[k]){  
            return 1;  
        }  
        return 3;  
    }  
    else{  
        if(S2[j] <= S3[k]){  
            return 2;  
        }  
        return 3;  
    }  
}  
  
// n -> 集合的大小  
int findMinDiffWeight(int n);  
  
int main()  
{  
    int n;  
    scanf("%d", &n);  
    for (int i = 0; i < n; i++)  
        scanf("%d", &S1[i]);  
    for (int i = 0; i < n; i++)  
        scanf("%d", &S2[i]);  
    for (int i = 0; i < n; i++)  
        scanf("%d", &S3[i]);  
    printf("%d\n", findMinDiffWeight(n));  
    return 0;  
}  

int findMinDiffWeight(int n) {
    int max = MaxNum;
    int arr[3]={0};
    while(arr[0]<n && arr[1]<n && arr[2]<n ){
        int res =DiffWeight(arr[0],arr[1],arr[2]);
        max = (res<max)?res:max;
        arr[xls_min(arr[0],arr[1],arr[2])-1]++;
    }
    return max;
}