#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int DFS(int** adj,int n,int* vis,int ind){
	int size = 1;
	for(int i=0;i<n;i++){
		if(adj[ind][i]==1 && !vis[i]){
			vis[i]=1;
			size += DFS(adj,n,vis,i);
		}
	}
	return size;
}

int noOfConnectedComponents(int** adj,int n){
	int* vis = (int*)calloc(n,sizeof(int));
	int count = 0;
	for(int ind=0;ind<n;ind++){
		if(!vis[ind]){
			vis[ind]=1;
			DFS(adj,n,vis,ind);
			count++;
		}
	}
	return count;
}

void sizeOfComponents(int** adj,int n){
	int* vis = (int*)calloc(n,sizeof(int));
	int net = noOfConnectedComponents(adj,n);
	int i = 0;
	int* sizes = (int*)malloc(net * sizeof(int));
	for(int ind=0;ind<n;ind++){
		if(!vis[ind]){
			vis[ind]=1;
			sizes[i++] = DFS(adj,n,vis,ind);
		}
	}
	for(int i=0;i<net-1;i++){
		bool swapped = false;
		for(int j=0;j<net-i-1;j++){
			if(sizes[j]>sizes[j+1]){
				int temp = sizes[j];
				sizes[j] = sizes[j+1];
				sizes[j+1] = temp;
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
	for(int i=0;i<net;i++)
		printf("%d ",sizes[i]);
	printf("\n");
}

int noOfBridges(int** adj,int n){
	int count=0;
	int connected = noOfConnectedComponents(adj,n);
	for(int j=0;j<n;j++){
		for(int i=j;i<n;i++){
			if(adj[i][j]==1){
				int* vis = (int*)calloc(n,sizeof(int));
				adj[i][j] = 0; adj[j][i] = 0;
				if(noOfConnectedComponents(adj,n) > connected){
					count++;
				}
				adj[i][j] = 1; adj[j][i] = 1;
			}
		}
	}
	return count;
}

int noOfArticulationPoints(int** adj,int n){
	int count=0;
	int connected = noOfConnectedComponents(adj,n);
	for(int i=0;i<n;i++){
		int* vis = (int*)calloc(n,sizeof(int));
		vis[i] = 1;
		int curr = 0;
		for(int j=0;j<n;j++){
			if(!vis[j]){
				vis[j]++;
				DFS(adj,n,vis,j);
				curr++;
			}
		}
		if(curr > connected)
				count++;
	}
	return count;
}

int main(){
	int n;
	scanf("%d",&n);
	int** adj = (int**)malloc(n*sizeof(int*));
	for (int i = 0; i < n; i++)
        adj[i] = (int*)calloc(n,sizeof(int));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&adj[i][j]);
		}
	}
	char ch;
	do{
		scanf("%c",&ch);
		if(ch=='a'){
			printf("%d\n",noOfConnectedComponents(adj,n));
		}
		else if(ch=='b'){
			sizeOfComponents(adj,n);
		}
		else if(ch=='c'){
			printf("%d\n",noOfBridges(adj,n));
		}
		else if(ch=='d'){
			printf("%d\n",noOfArticulationPoints(adj,n));
		}
	}while(ch!='x');
}