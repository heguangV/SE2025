#include <stdio.h>
#include <string.h>


int main() {
    int k = 0, n = 0; // k轮数，n人数
    scanf("%d %d", &k, &n);

    char arr[n][k]; // 存储投票

    // 输入数据
    for (int i = 0; i < n; i++) {
            scanf("%s", &arr[i]);
    }
    int amount = 0;
    // 处理每一轮投票
    for (int i = 0; i < n; i++) {
        if(strcmp(arr[i],arr[0])) amount++;
    }
    
    printf("%d\n", amount);
    
    return 0;
}