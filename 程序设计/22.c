#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** A;

void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int m;
    if (scanf("%d", &m) != 1) return 0;
    A = (double**)malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        A[i] = (double*)malloc((m + 1) * sizeof(double));
        for(int j = 0; j < m + 1; j++) {
            A[i][j] = 0.0;
            if (scanf("%lf", &A[i][j]) != 1) A[i][j] = 0.0;
        }
    }
    const double EPS = 1e-12;
    for(int i = 0; i < m; i++) {
        int p = i;
        for(int j = i + 1; j < m; j++) {
            if(fabs(A[j][i]) > fabs(A[p][i])) {
                p = j;
            }
        }
        /* swap rows i and p */
        for(int j = 0; j < m+1; j++) {
            swap(&A[i][j], &A[p][j]);    
        }
        /* check pivot */
        if (fabs(A[i][i]) < EPS) {
            printf("No Solution\n");
            /* free memory before exiting */
            for (int ii = 0; ii < m; ii++) free(A[ii]);
            free(A);
            return 0;
        }
        for(int j = i + 1; j < m; j++) {
            if(fabs(A[j][i]) > EPS) {
                double t = A[j][i] / A[i][i];
                for(int k = i; k < m + 1; k++) {
                    A[j][k] -= t * A[i][k];
                }
            }
        }
    }
    double* x = (double*)malloc(m * sizeof(double));
    for(int i = m - 1; i >= 0; i--) {
        double tmp = 0.0;
        for(int j = i + 1; j < m; j++) {
            tmp += A[i][j] * x[j];
        }
        x[i] = (A[i][m] - tmp) / A[i][i];
    }
    for(int i = 0; i < m; i++) {
        printf("%.2f\n", x[i]);
    }
    for (int i = 0; i < m; i++) free(A[i]);
    free(A);
    free(x);
    return 0;
}