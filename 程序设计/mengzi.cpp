#include<stdio.h>
#include<stdlib.h>
const int maxn = 200005;  
int n;  
int a[maxn];  
void findminandmax(int n); // you should finish this  
int cmp(int i, int j)  
{  
    if (i <= 0 || i > 2 * n || j <= 0 || j > 2 * n) return -2;  
    if (a[i] > a[j]) return 1;  
    if (a[i] == a[j]) return 0;  
    if (a[i] < a[j]) return -1;  
}  
int main()  
{  
    scanf("%d", &n);  
    for (int i = 1; i <= 2 * n; i++)  
        scanf("%d", &a[i]);  
    findminandmax(n);  
    return 0;  
}  
 
void findminandmax(int n) 
{ 
    int pt = 1;
    int max =1,min=1;
    while(pt<=2*n){
        int max_index = pt;
        int min_index = pt+1;
        if(cmp(max_index,min_index)<0){
            int temp = max_index;
            max_index = min_index;
            min_index = temp;
        }
        if(cmp(max_index,max)>0) max = max_index;
        if(cmp(min_index,min)<0) min = min_index;
        pt += 2;
    }
    printf("%d %d\n",min,max);
} 