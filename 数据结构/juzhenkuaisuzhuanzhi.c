#include <stdio.h>
int main() {
    int x,y,n;
    scanf("%d%d%d",&x,&y,&n);
    int a[n][3];
    int num[y];
    for(int i=0;i<y;i++){
        num[i]=0;
    }
    int cpot[y];
    for(int i=0;i<y;i++){
        cpot[i]=0;
    }
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
        num[a[i][1]-1]++;
    }
    for(int i=1;i<y;i++){
        cpot[i]=cpot[i-1]+num[i-1];
    }
    printf("num:");
    for(int i=0;i<y;i++){
        printf("%d,",num[i]);
    }
    printf("\n");
    printf("cpot:");
    for(int i=0;i<y;i++){
        printf("%d,",cpot[i]+1);
    }
    printf("\n");
    int ans[n][3];
    for(int i=0;i<n;i++){
        int col = a[i][1] - 1;
        int pos = cpot[col]++;
        ans[pos][0]=a[i][1];
        ans[pos][1]=a[i][0];
        ans[pos][2]=a[i][2];
    }
    for(int i=0;i<n;i++){
        printf("%d,%d,%d\n",ans[i][0],ans[i][1],ans[i][2]);
    }
    return 0;
}
