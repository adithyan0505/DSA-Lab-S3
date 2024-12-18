#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct job{
    int jid;
    int priority;
}* Job;

int parent(int i){
    return (i-1)/2;
}

void swap(Job* a,Job* b){
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void HeapifyUP(Job* PQ,int size){
    int i = size-1;
    while((i != 0) && (PQ[parent(i)]->priority > PQ[i]->priority)){
        swap(&PQ[parent(i)],&PQ[i]);
        i = parent(i);
    }
}

void HeapifyDown(Job* PQ,int size,int i){
    int smallest = i;
    int left = 2*i+1, right = 2*i+2;
    if((left < size) && (PQ[smallest]->priority > PQ[left]->priority))
        smallest = left;
    if((right < size) && (PQ[smallest]->priority > PQ[right]->priority))
        smallest = right;
    if(smallest != i){
        swap(&PQ[smallest],&PQ[i]);
        HeapifyDown(PQ,size,smallest);
    }
}

void LevelOrder(Job* heap,int size){
    printf("%d %d\n",heap[0]->jid,heap[0]->priority);
    for(int i=0;i <= (size-1)/2;i++){
        int left = 2*i+1, right = 2*i+2;
        if(left < size)
            printf("%d %d\n",heap[left]->jid,heap[left]->priority);
        if(right < size)
            printf("%d %d\n",heap[right]->jid,heap[right]->priority);
    }
}

void Add(Job* PQ,int* size,int jid,int p){
    Job new_Job = (Job)malloc(sizeof(struct job));
    new_Job->jid = jid;
    new_Job->priority=p;
    PQ[(*size)] = new_Job;
    HeapifyUP(PQ,++(*size));
}

void Schedule(Job* PQ,int size){
    swap(&PQ[0],&PQ[size-1]);
    HeapifyDown(PQ,size-1,0);
    printf("%d\n",PQ[size-1]->jid);
}

void Next_job(Job* PQ){
    printf("%d\n",PQ[0]->jid);
}

void Replace_priority(Job* PQ,int size,int jid,int new_priority){
    int i;
    for(i = 0;i < size;i++){
        if(PQ[i]->jid == jid)
            break;
    }
    if(i == size){
        printf("-1\n");
        return;
    }
    int old_severity = PQ[i]->priority;
    PQ[i]->priority = new_priority;
    if(new_priority > old_severity)
        HeapifyDown(PQ,size,i);
    else{
        while((i != 0)&&(PQ[parent(i)]->priority > PQ[i]->priority)){
            swap(&PQ[parent(i)],&PQ[i]);
            i = parent(i);
        }
    }
}

void Display(Job* PQ,int size)
{
    if(!size){
        printf("-1\n");
        return;
    }
    LevelOrder(PQ,size);
}

int main(){
    char ch;
    int jid,p;
    Job* PQ = (Job*)malloc(200*sizeof(Job));
    int size = 0;
    do
    {
        scanf(" %c",&ch);
        if(ch=='a'){
            scanf("%d %d",&jid,&p);
            Add(PQ,&size,jid,p);
        }
        else if(ch=='b'){
            if(!size)
                printf("-1\n");
            else{
                Schedule(PQ,size);
                size--;
            }
        }
        else if(ch=='c'){
            if(!size)
                printf("-1\n");
            else
                Next_job(PQ);
            
        }
        else if(ch=='d'){
            int new;
            scanf("%d %d",&jid,&new);
            Replace_priority(PQ,size,jid,new);
        }
        else if(ch=='e'){
            Display(PQ,size);
        }
    } while (ch!='g');
    
}