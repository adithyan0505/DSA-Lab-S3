#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge{
	int u;
	int v;
	int weight;
}* edge;

int comparator(const void* a, const void* b){
	edge edge_a = *(edge*)a; 
	edge edge_b = *(edge*)b;
	return (edge_a->weight - edge_b->weight);
}

int UltParent(int* parent,int node){
	if(node==parent[node])
		return node;
	return parent[node] = UltParent(parent,parent[node]);
}

void UnionBySize(int* parent,int* size,int u,int v){
	int ultp_u = UltParent(parent,u);
	int ultp_v = UltParent(parent,v);
	if(ultp_u == ultp_v) return;
	if(size[ultp_u] < size[ultp_v]){
		parent[ultp_u] = ultp_v;
		size[ultp_v] += size[ultp_u];
	}
	else{
		parent[ultp_v] = ultp_u;
		size[ultp_u] += size[ultp_v];
	}
}

void kruskal(edge* graph,int n,int graph_size){
	int* size = (int*)calloc(n,sizeof(int));
	int* parent = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		parent[i] = i;

	int mstWeight = 0;
	for(int i=0;i<graph_size;i++){
		int u = graph[i]->u;
		int v = graph[i]->v;
		int weight = graph[i]->weight;
		if(UltParent(parent,u) != UltParent(parent,v)){
			mstWeight += weight;
			UnionBySize(parent,size,u,v);
		}
	}
	printf("%d",mstWeight);
}

int main(){
	int n;
	scanf("%d",&n);
	edge* graph = (edge*)malloc((n*n)*sizeof(edge));
	int ind = 0;
	int val; char ch;
	for(int i=0;i<n;i++){
		scanf("%d%c",&val,&ch);
		while(ch!='\n'){
			edge temp = (edge)malloc(sizeof(struct Edge));
			temp->u = val;
			scanf("%d%c",&(temp->v),&ch);
			graph[ind++] = temp;
		}
	} ind = 0;
	for(int i=0;i<n;i++){
		scanf("%d%c",&val,&ch);
		while(ch!='\n'){
			scanf("%d%c",&(graph[ind++]->weight),&ch);
		}
	}

	qsort((void*)graph,ind,sizeof(edge),comparator);

	kruskal(graph,n,ind);
}