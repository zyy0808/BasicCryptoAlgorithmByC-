#include<stdio.h>
int CRT(int d,int c);
int main(){
	int mi[1000],Mi[1000],Ni[1000],bi[1000];
	int p;
	scanf("%d",&p);/*先输入阶数*/
	int i;
	for(i=0;i<p;i++){
		scanf("%d %d",&bi[i],&mi[i]);
	} 
	int sum=1;
	for(i=0;i<p;i++){
		sum=mi[i]*sum;
	}
	for(i=0;i<p;i++){
		Mi[i]=sum/mi[i];
	}
	for(i=0;i<p;i++){
		Ni[i]=CRT(Mi[i],mi[i]);
	}
	int sum2=0;
	for(i=0;i<p;i++){
		sum2=Mi[i]*Ni[i]*bi[i]+sum2;
	}
	int result=0;
	result=sum2%sum;
	if(result<0){
		result=sum+result;
	}
	printf("解为%d(mod %d)",result,sum);
	return 0;
}
int CRT(int d,int c){
	int ri[1000],qi[1000],si[1000],ti[1000];
	ri[0]=d;
	ri[1]=c;
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
	}
	return si[a-2];
}
