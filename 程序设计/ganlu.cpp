#include"stdio.h"
#include"math.h"

double cal_dis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double cal_r(double x ,double y){
    return fabs(x-y);
}

double min(double a,double b){
    return a<b?a:b;
}

double max(double a,double b){
    return a>b?a:b;
}

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
    return 1;
}

int main(){
    double count=0;
    int n;
    scanf("%d",&n);
    double x[2],y[2];
    scanf("%lf %lf %lf %lf",&x[0],&y[0],&x[1],&y[1]);
    double point[n][2];//0 x 1 y
    for(int i=0;i<n;i++){
        scanf("%lf %lf",&point[i][0],&point[i][1]);
    }
    int arr[n];//arr= diluoshunxu r =banjing
    double r[n];// jilu banjing
    for(int i=0;i<n;i++){
        arr[i] = i;
    }
    do//fangzhi tiaoguo diyi xulie
    {
        double res = 0;
        for(int i=0;i<n;i++){
            r[i] =min(min(cal_r(point[arr[i]][0],x[0]),cal_r(point[arr[i]][0],x[1])),min(cal_r(point[arr[i]][1],y[0]),cal_r(point[arr[i]][1],y[1])));//diandaobian
            for (int j=0;j<i;j++){//bianli qianmian de yuan
                double dis = 1000;
                dis = cal_dis(point[arr[i]][0],point[arr[i]][1],point[arr[j]][0],point[arr[j]][1]);
                r[i] = min(r[i], dis-r[j]);//fangzhi zai qita yuan nei
            }
            if(r[i]<0.0) r[i]=0.0;
            res+= r[i]*r[i]*3.1415926;
        }
        count = max(count,res);
    }while (next_permutation(arr, n));
    double ans = fabs(x[1]-x[0])*fabs(y[1]-y[0]) - count;
    printf("%.0lf\n", ans);
    return 0;
}