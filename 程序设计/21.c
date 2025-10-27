#include<stdio.h>

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    if (m == 0) {
    printf("1\n");
    } 
    else {
        if (n == 1) {
            printf("2\n");
        } 
        else if (n == 2) {
            if (m > 1) {
                printf("4\n");  
            } 
            else {
                printf("3\n");  
            }
        } 
        else {
            if (m == 1) {
            printf("4\n");
            } 
            else {
                if (m == 2) {
                    printf("7\n");  
                } 
                else {
                    printf("8\n");  
                }
        }
        }    
    }
    return 0;
}