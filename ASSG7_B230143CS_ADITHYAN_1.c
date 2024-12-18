#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
	int val;
	int weight;
	int parent;
}* edge;

int parent(int i){
    return (i-1)/2;
}

void swap(edge* a,edge* b){
    edge temp = *a;
    *a = *b;
    *b = temp;
}

void Insert(edge* pq,int pos,int v,int p,int weight){
	pq[pos] = (edge)malloc(sizeof(struct Edge));
	pq[pos]->val = v;
	pq[pos]->parent = p;
	pq[pos]->weight = weight;

	int i = pos;
	while((i>0) && (pq[parent(i)]->weight > pq[i]->weight)){
		swap(&pq[parent(i)],&pq[i]);
		i = parent(i);
	}
}

void heapify_down(edge* pq,int size,int i){
	int smallest = i;
	int left = 2*i+1, right=2*i+2;
	if((left < size) && (pq[left]->weight < pq[smallest]->weight))
		smallest = left;
	if((right < size) && (pq[right]->weight < pq[smallest]->weight))
		smallest = right;
	if(smallest != i){
		swap(&pq[smallest],&pq[i]);
		heapify_down(pq,size,smallest);
	}
}

edge extract_min(edge* pq,int size){
	swap(&pq[0],&pq[size-1]);
	heapify_down(pq,size-1,0);
	return pq[size-1];
}

void Sequence(int** adj,int n,int x){
	int* vis = (int*)calloc(n,sizeof(int));
	edge* pq = (edge*)malloc(n*sizeof(edge));
	Insert(pq,0,x,-1,0);
	int size = 1;
	while(size>0){
		edge node = extract_min(pq,size);
		size--;
		int vertex = node->val;
		int parent = node->parent;
		int weight = node->weight;
		if(vis[vertex]==1) continue;
		vis[vertex] = 1;
		if(parent!=-1)
			printf("%d %d (%d) ",parent,vertex,weight);
		for(int i=0;i<n;i++){
			if(adj[vertex][i]){
				if(!vis[i]){
					Insert(pq,size,i,vertex,adj[vertex][i]);
					size++;
				}
			}
		}
	}
	printf("\n");
	free(vis);
    free(pq);
}

void TotalWeight(int** adj,int n){
	int total = 0;
	int* vis = (int*)calloc(n,sizeof(int));
	edge* pq = (edge*)malloc(n*sizeof(edge));
	Insert(pq,0,0,-1,0);
	int size = 1;
	while(size>0){
		edge node = extract_min(pq,size);
		size--;
		int vertex = node->val;
		int parent = node->parent;
		int weight = node->weight;
		if(vis[vertex]==1) continue;
		vis[vertex] = 1;
		total += weight;	
		for(int i=0;i<n;i++){
			if(adj[vertex][i]){
				if(!vis[i]){
					Insert(pq,size,i,vertex,adj[vertex][i]);
					size++;
				}
			}
		}
	}
	printf("%d\n",total);
}

int main(){
	int n;
	scanf("%d",&n);
	int** adj = (int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		adj[i] = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			scanf("%d",&adj[i][j]);
	}
	char ch;
	do{
		scanf("%c",&ch);
		if(ch=='s'){
			int x;
			scanf("%d",&x);
			Sequence(adj,n,x);
		}
		else if(ch=='b')
			TotalWeight(adj,n);
	}while(ch!='e');
}