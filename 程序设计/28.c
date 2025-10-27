#include <stdio.h>
#include <stdlib.h>
#include <math.h> // For acos and cos

typedef long long ll;

// 定义2x2矩阵结构体
typedef struct {
    ll mat[2][2];
    int mod; // 存储模数
} Matrix;

// 创建一个单位矩阵
Matrix create_identity_matrix(int mod) {
    Matrix I;
    I.mod = mod;
    I.mat[0][0] = 1; I.mat[0][1] = 0;
    I.mat[1][0] = 0; I.mat[1][1] = 1;
    return I;
}

// 创建一个零矩阵
Matrix create_zero_matrix(int mod) {
    Matrix Z;
    Z.mod = mod;
    Z.mat[0][0] = 0; Z.mat[0][1] = 0;
    Z.mat[1][0] = 0; Z.mat[1][1] = 0;
    return Z;
}

// 矩阵乘法：C = A * B
Matrix multiply_matrices(Matrix A, Matrix B) {
    Matrix C = create_zero_matrix(A.mod); // 结果矩阵初始化为零矩阵
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % C.mod;
            }
        }
    }
    return C;
}

// 矩阵快速幂：base^exp
Matrix matrix_pow(Matrix base, ll exp) {
    Matrix res = create_identity_matrix(base.mod); // 结果初始化为单位矩阵
    Matrix p = base; // 当前幂的基数

    while (exp > 0) {
        if (exp % 2 == 1) { // 如果指数是奇数
            res = multiply_matrices(res, p);
        }
        p = multiply_matrices(p, p); // 基数平方
        exp /= 2; // 指数减半
    }
    return res;
}

int main() {
    int x, y, mod;
    scanf("%d %d %d", &x, &y, &mod);
    const double pi = acos(-1.0);
    const double phi = cos(36.0 * pi / 180.0) * 2.0;
    ll first_val = (ll)(x * phi * phi) - 1; // 对应 S_{x,1}
    ll second_val = first_val + first_val - x + 1; // 对应 S_{x,2}

    // 处理 y=1 和 y=2 的特殊情况
    if (y == 1) {
        printf("%lld\n", (first_val % mod + mod) % mod);
        return 0;
    } else if (y == 2) {
        printf("%lld\n", (second_val % mod + mod) % mod);
        return 0;
    }
    Matrix P;
    P.mod = mod;
    P.mat[0][0] = 1; P.mat[0][1] = 1;
    P.mat[1][0] = 1; P.mat[1][1] = 0;
    Matrix F;
    F.mod = mod;
    F.mat[0][0] = (first_val % mod + mod) % mod;
    F.mat[1][0] = ((second_val - first_val) % mod + mod) % mod;
    F.mat[0][1] = 0; 
    F.mat[1][1] = 0;    
    Matrix P_pow = matrix_pow(P, y - 1);
    Matrix Result_Vector = multiply_matrices(P_pow, F);
    printf("%lld\n", Result_Vector.mat[0][0]);

    return 0;
}