#include <stdio.h>
#include <stdlib.h>
int L[11]={0,1,2,3,4,5,6,7,8,9,10},P[11]={0,1,5,8,9,10,17,17,20,23,28};
int num[11]={0};
void fun(int n) {
    int i,j,max;
 	for(i=1;i<=n;i++){
            max=P[i];
 	 		for(j=1;j<=i;j++){
 	 		    max=P[j]+num[i-j] >=max? (P[j]+num[i-j]):max;
    }
    num[i]=max;
    }
}
int main() {
    int n;scanf("%d",&n);
    fun(n);
    printf("%d ",num[n]);
    return 0;
}
