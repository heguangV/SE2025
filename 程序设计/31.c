#include <stdio.h>
#include <stdlib.h> 
int* lg_arr;     
int** st_table;   
int* a_arr;      

int query_sparse_table(int ql, int k, int n) {
    if(a_arr[ql]<k) return -1;
    int cur = a_arr[ql];
    int pos = ql+1;
    for(int i= lg_arr[n]; i>=0; i--){
        if(pos+(1<<i) - 1 <= n && (cur&st_table[pos][i])>=k){
            cur = cur & st_table[pos][i];
            pos += (1<<i);
        }
    }
    return pos-1;
}

int main(){
    int n;
    scanf("%d",&n);

    lg_arr = (int *)malloc((n+1)*sizeof(int));
    lg_arr[0] = 0; // Not strictly used for 1-based, but good practice
    lg_arr[1] = 0; // log2(1) is 0
    for(int i=2;i<=n;i++){
        lg_arr[i] = lg_arr[i/2]+1;
    }

    st_table = (int **)malloc((n+1)*sizeof(int *));
    for(int i=0;i<=n;i++){ // Allocate rows (i=0 unused for 1-based a_arr)
        st_table[i] = (int *)malloc((lg_arr[n]+1)*sizeof(int));
    }
    a_arr = (int *)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++){
        scanf("%d",&a_arr[i]);
    }

    for(int i=1;i<=n;i++){ // Start from i=1 for 1-based indexing
        st_table[i][0] = a_arr[i];
    }

    for(int j=1;j<=lg_arr[n];j++){
        for(int i=1; i + (1<<j) - 1 <= n; i++){ // Correct loop condition: ensures entire 2^j block is within bounds
            st_table[i][j] = st_table[i][j-1] & st_table[i + (1<<(j-1))][j-1];
        }
    }
    int q_count;
    scanf("%d",&q_count);
    while(q_count--){
        int ql, qr; // Renamed from 'l', 'r' to avoid conflict
        scanf("%d%d",&ql,&qr);
        printf("%d ", query_sparse_table(ql, qr, n));
    }
    printf("\n");
    free(lg_arr);
    free(a_arr);
    for(int i=0;i<=n;i++){
        free(st_table[i]);
    }   
    free(st_table);

    return 0;
}