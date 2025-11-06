#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 计算10的幂次方
long long power10(int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= 10;
    }
    return result;
}

// 将数字转换为数字数组
int* getArray(long long x, int* size) {
    long long temp = x;
    int count = 0;
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    int* number = (int*)malloc(count * sizeof(int));
    temp = x;
    for (int i = count - 1; i >= 0; i--) {
        number[i] = temp % 10;
        temp /= 10;
    }
    *size = count;
    return number;
}

// 检查函数
long long check(long long m, long long limit) {
    long long sum = 0;
    int base_size, now_size;
    int* base = getArray(m, &base_size);
    int* now = getArray(limit, &now_size);
    
    // 处理长度小于base_size的情况
    for (int length = 1; length < base_size; ++length) {
        sum += m / power10(base_size - length) - power10(length - 1) + 1;
    }
    
    // 处理长度大于等于base_size的情况
    for (int length = base_size; length <= now_size; ++length) {
        long long shift = m * power10(length - base_size);
        long long min_val = (length != base_size) ? shift - 1 : shift;
        long long actual_limit = (limit < min_val) ? limit : min_val;
        sum += actual_limit - power10(length - 1) + 1;
    }
    
    free(base);
    free(now);
    return sum;
}

int main() {
    long long m, num;
    scanf("%lld %lld", &m, &num);
    
    // 预计算10的18幂次方
    long long pw[19];
    pw[0] = 1;
    for (int i = 1; i <= 18; ++i) {
        pw[i] = pw[i-1] * 10;
    }
    
    if (check(m, m) > num) {
        printf("0\n");
        return 0;
    }
    
    long long l = m, r = 5000000000000000000LL;
    long long ans = 0;
    
    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (check(m, mid) >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}