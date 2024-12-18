#include <stdio.h>
#include <stdlib.h>

void KMP(char* S,int slen, char* P,int plen){
	int* LPS = (int*)calloc(plen,sizeof(int));
	//constructing LPS
	int len = 0, it = 1;
	while(it < plen){
		if(P[it] == P[len]){
			LPS[it] = ++len;
			it++;
		}
		else{
			if(len!=0)
				len = LPS[len-1];
			else
				it++;
		}
	}
	//search
	int i = 0, j = 0, count = 0, last;
	while(i < slen){
		if(S[i] == P[j]){
			i++; j++;
		}
		else{
			if(j==0)
				i++;
			else
				j = LPS[j-1];
		}
		if(j == plen){
			last = i-j; count++;
			j = LPS[j-1];
		}
	}
	if(count)
		printf("%d %d",last,count);
	else
		printf("-1");
}

int main(){
	char S[1000000], P[100000];
	char ch;
	int slen = 0, plen = 0;
	while((ch=getchar())!='\n'){
		S[slen++] = ch;
	}
	while((ch=getchar())!='\n'){
		P[plen++] = ch;
	}
	KMP(S,slen,P,plen);
	return 0;
}