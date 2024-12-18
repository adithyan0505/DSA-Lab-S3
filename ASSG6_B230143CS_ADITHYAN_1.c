#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node{
	int val;
	int weight;
	struct Node *next;
}* node;

struct pair{
	int vertex;
	int distance;
};

int parent(int i){
    return (i-1)/2;
}

void swap(struct pair* a,struct pair* b){
    struct pair temp = *a;
    *a = *b;
    *b = temp;
}

void Insert(struct pair* pq,int ind,int ver,int dis){
	pq[ind].vertex = ver;
	pq[ind].distance = dis;
	while((ind!=0) && (pq[parent(ind)].distance > pq[ind].distance)){
		swap(&pq[parent(ind)],&pq[ind]);
		ind = parent(ind);
	}
}

void heapify_down(struct pair* pq,int size,int i){
	int smallest = i;
	int left = 2*i+1, right = 2*i+2;
	if((left < size) && (pq[left].distance < pq[smallest].distance))
		smallest = left;
	if((right < size) && (pq[right].distance < pq[smallest].distance))
		smallest = right;
	if(smallest != i){
		swap(&pq[smallest],&pq[i]);
		heapify_down(pq,size,smallest);
	}
}

struct pair extract_min(struct pair* pq,int n){
	swap(&pq[n-1],&pq[0]);
	heapify_down(pq,n-1,0);
	return pq[n-1];
}

int* dijkstra(node* adj,int n,int s){
	int* dist = (int*)malloc((n+1)*sizeof(int));
	for(int i=0;i<=n;i++)
		dist[i] = INT_MAX;
	dist[s] = 0;
	struct pair* pq = (struct pair*)calloc(n,sizeof(struct pair)); ////
	Insert(pq,0,s,0);
	int size = 1;
	while(size > 0){
		struct pair u = extract_min(pq,size--);
		node curr = adj[u.vertex];
		int dis = u.distance;
		while(curr){
			int edgeWeight = curr->weight;
			int adjNode = curr->val;
			if(dis + edgeWeight < dist[adjNode]){
				dist[adjNode] = dis + edgeWeight;
				Insert(pq,size++,adjNode,dist[adjNode]);
			}
			curr = curr->next;
		}
	}
	return dist;
}

int main(){
	int n,v;
	char ch;
	scanf("%d%c",&n,&ch);
	node* adj = (node*)malloc((n+1)*sizeof(node));
	for(int i=0;i<=n;i++)
		adj[i] = NULL;
	for(int i=1;i<=n;i++){
		scanf("%d%c",&v,&ch);
		node prev = NULL;
		while(ch!='\n'){
			node temp = (node)malloc(sizeof(struct Node));
			scanf("%d%c",&(temp->val),&ch);
			temp->next = NULL;
			if(prev)
				prev->next = temp;
			else
				adj[v] = temp;
			prev = temp;
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%d%c",&v,&ch);
		node temp = adj[v];
		while(ch!='\n'){
			scanf("%d%c",&(temp->weight),&ch);
			temp = temp->next;
		}
	}
	int s;
	scanf("%d",&s);
	/*for(int i=1;i<=n;i++){
		node vertex = adj[i];
		while(vertex){
			printf("%d ",vertex->weight);
			vertex = vertex->next;
		}
		printf("\n");
	}*/
	int* dist = dijkstra(adj,n,s);
	for(int i=1;i<=n;i++){
		printf("%d",dist[i]);
		if(i!=n) printf(" ");
	}
}