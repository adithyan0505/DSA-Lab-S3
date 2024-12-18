#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Floyd_Warshall(int** adj,int n){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(adj[i][j] > adj[i][k] + adj[k][j])
					adj[i][j] = adj[i][k] + adj[k][j];
			}
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);
	int** adj = (int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		adj[i] = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&adj[i][j]);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(adj[i][j]==-1)
				adj[i][j]=INT_MAX/4;
		}
	}
	Floyd_Warshall(adj,n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(adj[i][j] > 100)
				adj[i][j]=-1;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d",adj[i][j]);
			if(j!=n-1)
				printf(" ");
		}
		if(i!=n-1)
			printf("\n");
	}
}