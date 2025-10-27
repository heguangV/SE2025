#include<stdio.h>
const int MOD = 1000000009;
typedef long long ll;

void sort(ll* arr, int left, int right) {
    if(left >= right) return;
    int i = left, j = right, pivot = arr[left];
    while(i < j) {
        while(i < j && arr[j] > pivot) j--;
        if(i < j) arr[i++] = arr[j];
        while(i < j && arr[i] < pivot) i++;
        if(i < j) arr[j--] = arr[i];
    }
    arr[i] = pivot;
    sort(arr, left, i - 1);
    sort(arr, i + 1, right);
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);  
    ll array[n];
    int a=0;
    for(int i = 0; i < n; i++){
        scanf("%lld", &array[i]);
    }
    sort(array,0,n-1);
    if(n == m) {
        ll ans = 1;
        for(int i = 0; i < n; i++){
            ans = (ans * (array[i] % MOD)) % MOD;
        }
        printf("%lld\n", ans);
        return 0;
    }
    ll ans = 1;
    int cnt = 0;
    int flag = 1;
    if(m%2==1){
        ans = (ans * (array[n-1] % MOD)) % MOD;
        m--;
        cnt++;
        if(array[n-1] < 0) flag = -1;
    }
    int left = 0, right = n - 1 - cnt;
    while(m > 0){
        ll left_mul = array[left]  * array[left + 1] ;
        ll right_mul = array[right] * array[right - 1] ;
        if(left_mul * flag> right_mul* flag){
            ans = (ans * left_mul%MOD) % MOD;
            left += 2;
        } else {
            ans = (ans * right_mul%MOD) % MOD;
            right -= 2;
        }
        m -= 2;
    }
    printf("%lld\n", ans);
}