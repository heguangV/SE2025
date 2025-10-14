#include <stdio.h>

int next_permutation(int *arr, int n) {//chuangzaochu suoyou de pai lie
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) i--;
    if (i < 0) return 0;
    int j = n - 1;
    while (arr[j] <= arr[i]) j--;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    int left = i + 1, right = n - 1;
    while (left < right) {
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
        if(i==n-1) printf("\n");
        else printf(" ");
    }
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i] = i+1;
    }
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
        if(i==n-1) printf("\n");
        else printf(" ");
    }
    while(next_permutation(arr,n));
    return 0;
}