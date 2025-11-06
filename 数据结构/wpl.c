#include<stdio.h>
#include<stdlib.h>

int* arr;
int qsort_cmp(const void* a,const void* b){
    return (*(int*)a)-(*(int*)b);
}

int main(){
    int n;
    scanf("%d",&n);
    arr=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr,n,sizeof(int),qsort_cmp);
    int sum = 0;
    while(n!=1){
        int a=arr[0];
        int b=arr[1];
        for(int i=2;i<n;i++){
            arr[i-2]=arr[i];
        }
        arr[n-2]=a+b;
        sum += a+b;
        n--;
        qsort(arr,n,sizeof(int),qsort_cmp);
    }
    printf("WPL=%d\n",sum);
    free(arr);
    return 0;
}