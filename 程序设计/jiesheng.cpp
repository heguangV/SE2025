#include<stdio.h>

//def fanzhuan()

int main(){
    int n =0;
    char a[1000]={0};
    scanf("%d %s",&n,&a);
    int count = 0;
    for(int i = 0;i < n;i++){
        if(a[i]=='1') count++;
    }
    if(count%2 != 0){
        printf("-1\n");
        return 0;
    } 
    int amount =0;
    for(int i = 0;i< n-1; i++){//mo ni jie sheng
        if(a[i]=='1'){
            a[i]='0';
            if(a[i+1]=='0'){
                a[i+1]='1';
            } 
            else{
                a[i+1]='0';
            } 
            amount++;
        }
    }
    printf("%d\n",amount);
    return 0;
}