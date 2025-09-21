#include <stdio.h>
#include <stdlib.h>

void paixu(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void cal(int *arr, int r, int n) {
    arr[n-1]--;
    int i=n-1;
    while(i>0 && arr[i] < arr[i-1]) {
        int temp = arr[i];
        arr[i] = arr[i-1];
        arr[i-1] = temp;
        i--;
    }
    if(r-1 > 0) {
        cal(arr, r - 1, n);
    }
}

int main() {
    int n=0,R=0;
    scanf("%d %d",&n,&R);
    int a[n];
    int b[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int c[n];
    for(int i=0;i<n;i++){
        c[i] = abs(a[i] - b[i]);
    }
    paixu(c, n);
    cal(c, R, n);
    int amount=0;
    for(int i=0;i<n;i++){
        amount += c[i]*c[i];
    }
    printf("%d\n", amount);
    return 0;
}




