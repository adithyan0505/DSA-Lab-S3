#include <stdio.h>
#include <string.h>

int max(int a,int b){
	return (a > b ? a:b);
}

void boyermoore(char *T,int tlen,char *P,int plen){
	int badchar[256];
	for(int i=0;i<256;i++)
		badchar[i] = -1;
	for(int i=0;i<plen;i++)
		badchar[(int)P[i]] = i;

	int shift=0;
	while(shift <= (tlen - plen)){
		int j = plen - 1;
		while(j >= 0 && P[j]==T[shift + j])
			j--;
		if(j < 0){
			printf("%d",shift);
			return;
		}
		else
			shift += max(1, j - badchar[T[shift + j]]);
	}
}

int main(){
	char T[1000000], P[10000];
	char ch;
	int tlen = 0, plen = 0;
	while((ch=getchar())!='\n'){
		T[tlen++] = ch;
	}
	while((ch=getchar())!='\n'){
		P[plen++] = ch;
	}
	boyermoore(T,tlen,P,plen);
	return 0;
}