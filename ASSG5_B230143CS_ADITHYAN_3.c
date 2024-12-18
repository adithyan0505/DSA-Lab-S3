#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node{
	int val;
	struct Node* next;
}* node;

bool hasCycle(node* adj,int* vis,int* pathvis,int curr){
	vis[curr] = 1;
	pathvis[curr] = 1;
	node vertex = adj[curr];
	while(vertex){
		if(!vis[vertex->val]){
			if(hasCycle(adj,vis,pathvis,vertex->val)==true)
				return true;
		}else if(pathvis[vertex->val]){
			return true;
		}
		vertex = vertex->next;
	}
	pathvis[curr]=0;
	return false;
}

void isDAG(node* adj,int n){
	int* vis = (int*)calloc((n+1),sizeof(int));
	int* pathvis = (int*)calloc((n+1),sizeof(int));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			if(hasCycle(adj,vis,pathvis,i)==true){
				printf("-1\n");
				return;
			};
		}
	}
	printf("1\n");
}

void dfs(node* adj,int* vis,int* st,int* top,int curr,int flag){
	vis[curr]=1;
	node vertex = adj[curr];
	while(vertex){
		if(!vis[vertex->val]){
			dfs(adj,vis,st,top,vertex->val,flag);
		}
		vertex = vertex->next;
	}
	if(flag)
		st[(*top)++] = curr;
}

void countStronglyConnectedComponents(node* adj,int n){
	int* vis = (int*)calloc((n+1),sizeof(int));
	int* st = (int*)malloc(n*sizeof(int));
	int top = 0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(adj,vis,st,&top,i,1);
		}
	}
	node* transpose = (node*)malloc((n+1)*sizeof(node));
	for(int i=0;i<=n;i++)
		transpose[i]=NULL;
	for(int i=1;i<=n;i++){
		vis[i] = 0;
		node vertex = adj[i];
		while(vertex){
			node temp = (node)malloc(sizeof(struct Node));
			temp->val = i;
			temp->next = transpose[vertex->val];
			transpose[vertex->val] = temp;
			vertex = vertex->next;
		}
	}
	int scc=0;
	while(top>0){
		int popped = st[--top];
		if(!vis[popped]){
			dfs(transpose,vis,st,&top,popped,0);
			scc++;
		}
	}
	printf("%d\n",scc);

}

int main(){
	int n,m;
	char ch; int num = 0,ind;
	scanf("%d %d",&n,&m);
	getchar();
	node* adj = (node*)malloc((n+1)*sizeof(node));
	for(int i=0;i<=n;i++){
		adj[i] = NULL;
	}
	for(int i=1;i<=n;i++){
		ch = getchar();
		ind = ch-'0';
		while((ch=getchar())!='\n'){
			if(isdigit(ch)){
				num *= 10;
				num += ch-'0';
			}else{
				if(num!=0){
					node vertex = (node)malloc(sizeof(struct Node));
					vertex->val = num;
					vertex->next = adj[ind];
					adj[ind] = vertex;
					num = 0;
				}
			}
		}
		if(num!=0){
			node vertex = (node)malloc(sizeof(struct Node));
			vertex->val = num;
			vertex->next = adj[ind];
			adj[ind] = vertex;
			num = 0;
		}
	}
	/*for(int i=1;i<=n;i++){
		node vertex = adj[i];
		while(vertex){
			printf("%d ",vertex->val);
			vertex = vertex->next;
		}
		printf("\n");
	}*/
	do{
		scanf("%c",&ch);
		if(ch=='a')
			isDAG(adj,n); // true if not cyclic	
		else if(ch=='b')
			countStronglyConnectedComponents(adj,n);
	}while(ch!='x');
}
