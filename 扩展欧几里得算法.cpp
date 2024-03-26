#include<stdio.h>
int main(){
	int ri[1000],qi[1000],si[1000],ti[1000];
	scanf("%d %d",&ri[0],&ri[1]);
	si[0]=1;
	si[1]=0;
	ti[0]=0;
	ti[1]=1;
	qi[0]=0;
	int x=1;
	int t=2,j=1,a=2,b=2;
    for(int y=1;x!=0;y++){
		ri[t]=ri[t-2]%ri[t-1];
		qi[j]=ri[j-1]/ri[j];
		si[a]=si[a-2]-si[a-1]*qi[a-1];
		ti[b]=ti[b-2]-ti[b-1]*qi[b-1];
		t++;
		j++;
		a++;
		b++;
		x=ri[t-1];
		printf("%d %d %d %d\n",ri[t-2],qi[j-1],si[a-2],ti[b-2]);
	}
	if(ti[b-2]<0){
		ti[b-2]=ti[b-2]+ri[0];
	}
	printf("%d(mod%d)的逆元为：%d，%d(mod%d)的逆元为： %d \n",ri[0],ri[1],si[a-2],ri[1],ri[0],ti[b-2]);
	return 0;
}
