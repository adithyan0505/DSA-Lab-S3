#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool BFS(int** adj,int n,int* color,int start){
	int* q = (int*)malloc(n*sizeof(int));
	int front=0, rear=0;
	q[rear++]=start;
	color[start] = 0;
	while(front < rear){
		int node = q[front++];
		for(int i=0;i<n;i++){
			if(adj[node][i]){
				if(color[i]==-1){
					color[i] = !color[node];
					q[rear++] = i;
				}else if(color[i]==color[node]){
					free(q);
					return false;
				}
			}
		}
	}
	free(q);
	return true;
}

void isBipartite(int** adj,int n){
	int* color = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		color[i] = -1;
	for(int i=0;i<n;i++){
		if(color[i]==-1){
			if(BFS(adj,n,color,i)==false){
				printf("-1\n");
				return;
			}
		}
	}
	printf("1\n");
}

bool BFS_cycle(int** adj,int n,int* vis,int curr){
	int* q = (int*)malloc(n*sizeof(int));
	int parents[n];
	parents[0] = -1;
	int front = 0, rear = 0;
	q[rear++] = curr;
	vis[curr] = 1;
	while(front < rear){
		int node = q[front++];
		int parent = parents[node];
		for(int i=0;i<n;i++){
			if(adj[node][i]){
				if(!vis[i]){
					vis[i] = 1;
					parents[i]=node;
					q[rear++] = i;
				}else if(i != parent){
					return true;
				}
			}
		}
	}
	return false;
}

void hasCycle(int** adj,int n){
	int* vis = (int*)calloc(n,sizeof(int));
	for(int i=0;i<n;i++){
		if(!vis[i]){
			if(BFS_cycle(adj,n,vis,i)==true){
				printf("1\n");
				return;
			}
		}
	}
	printf("-1\n");
}

bool isTreeHelper(int** adj,int n){
	int* vis = (int*)calloc(n,sizeof(int));
	if(n==1)
		return true;
	int edges = 0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(adj[i][j]){
				edges++;
			}
		}
	}
	if(edges != n-1)
		return false;
	if(BFS_cycle(adj,n,vis,0))
		return false;
	return true;
}

void isTree(int** adj,int n){
	if(isTreeHelper(adj,n)==true)
		printf("1\n");
	else
		printf("-1\n");
}

int main(){
	int n;
	scanf("%d",&n);
	int** adj = (int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		adj[i] = (int*)calloc(n,sizeof(int));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			scanf("%d",&adj[i][j]);
	}
	char ch;
	do{
		scanf("%c",&ch);
		if(ch=='a')
			isBipartite(adj,n);
		if(ch=='b')
			hasCycle(adj,n);
		if(ch=='c')
			isTree(adj,n);
	}while(ch!='x');
}