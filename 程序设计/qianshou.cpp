#include <stdio.h>
#include <math.h>

typedef long long ll;

ll cal_dis(int x1,int y1,int x2,int y2){
    return (ll)(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

ll check(int point[][2],int n,int x1,int x2){
        int arr[2]={1,1};
        ll len =cal_dis(point[x1][0],point[x1][1],point[x2][0],point[x2][1]);
        ll a = point[x2][1]-point[x1][1];
        ll b = point[x1][0]-point[x2][0];
        ll c = point[x2][0]*point[x1][1]-point[x2][1]*point[x1][0];
        for(int i=0;i<n;i++){
            if(i==x1||i==x2) continue;
            ll res = a*point[i][0]+b*point[i][1]+c;
            if(res>0) arr[0]=0;
            if(res<0) arr[1]=0;
            if(res==0){
                if(cal_dis(point[i][0],point[i][1],point[x1][0],point[x1][1])>len||
                   cal_dis(point[i][0],point[i][1],point[x2][0],point[x2][1])>len){
                    arr[0]=0;
                    arr[1]=0;
                       break;
                   }
            }
            if(arr[0]==0&&arr[1]==0) {
                break;// zailiangbian like tuichu
            }
        }
        if(arr[0]||arr[1]) return len;
    return 0;
}
int main(){
    int n;
    double count=0;
    scanf("%d",&n);
    int point[n][2]; //0 x 1 y
    for(int i=0;i<n;i++){
        scanf("%d %d",&point[i][0],&point[i][1]);
    } 
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            count+=sqrt(check(point,n,i,j));
        }
    }
    printf("%.10f\n",count);
    return 0;
}