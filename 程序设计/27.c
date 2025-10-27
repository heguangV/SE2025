#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int * arr;
int * use;
int qsort_cmp(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int search(int still, int now ,int n, int len, int last){// still:剩多少 now：当前多少
    if(still == 0){
        return 1;
    }
    if(now == 0){
       return search(still - 1, len,n,len,0);
    }
    int failed = 0;
    for(int i=last;i<n;i++){
        if(!use[i]&&now-arr[i]>=0&& failed!=arr[i]){
            use[i] = 1;
            if(search(still, now - arr[i], n,len,i)){
                return 1;
            }
            use[i] = 0;
            failed = arr[i];
            if(now == arr[i]|| now - arr[i] ==0){
                return 0;
            }
        }
    }

    return 0;
}

int main(){
    int n;
    scanf("%d",&n);
    arr = (int *)malloc(n * sizeof(int));
    use = (int *)malloc(n * sizeof(int));
    memset(use, 0, n * sizeof(int));
    int max = -1;
    int sum = 0;
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        if(arr[i]>max){
            max = arr[i];
        }
        sum += arr[i];
    }
    qsort(arr,n,sizeof(int),qsort_cmp);
    for(int i=max;i<=sum;i++){
        if(sum%i){
            continue;
        }
        memset(use, 0, n * sizeof(int));
        if(search(sum/i,i,n,i,0)){
            printf("%d\n",i);
            break;
        }
    }
    free(arr);
    free(use);
    return 0;
}