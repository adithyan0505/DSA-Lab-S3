#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* next;
}* Node;

void insert(Node* hashTable,int size,int key){
    int index = key%size;
    Node new = (Node)malloc(sizeof(struct Node));
    new->key = key;
    if(hashTable[index]==NULL){
        new->next = NULL;
        hashTable[index] = new;
    }else{
        Node curr = hashTable[index];
        Node prev = NULL;
        while(curr!=NULL && curr->key < key){
            prev = curr;
            curr = curr->next;
        }
        if(curr && curr->key == key){
            printf("-1\n");
            free(new);
            return;
        }
        if(prev==NULL){
            new->next = curr;
            hashTable[index] = new;
        }else{
            new->next = curr;
            prev->next = new;
        }
    }
}

void search(Node* hashTable,int size,int key){
    int index = key%size;
    Node node = hashTable[index];
    int pos = 1;
    while(node){
        if(node->key == key)
            break;
        pos++;
        node = node->next;
    }
    if(node == NULL){
        printf("-1\n");
        return;
    }
    printf("%d %d\n",index,pos);
}

void delete(Node* hashTable,int size,int key){
    int index = key%size;
    Node curr = hashTable[index];
    Node prev = NULL;
    int pos = 1;
    while(curr!=NULL && curr->key != key){
        prev = curr;
        curr = curr->next;
        pos++;
    }
    if(curr==NULL){
        printf("-1\n");
        return;
    }
    if(prev==NULL)
        hashTable[index] = curr->next;
    else
        prev->next = curr->next;
    free(curr);
    printf("%d %d\n",index,pos);
}

void update(Node* hashTable,int size,int oldKey,int newKey){
    int oldindex = oldKey%size;
    Node curr0 = hashTable[oldindex];
    Node prev0 = NULL;
    int pos = 1;
    while(curr0!=NULL && curr0->key != oldKey){
        prev0 = curr0;
        curr0 = curr0->next;
        pos++;
    }
    if(curr0==NULL){
        printf("-1\n");
        return;
    }
    int newindex = newKey%size;
    Node curr1 = hashTable[newindex];
    Node prev1 = NULL;
    while(curr1 && curr1->key < newKey){
        prev1 = curr1;
        curr1 = curr1->next;
    }
    if(curr1 && curr1->key == newKey){
        printf("-1\n");
        return;
    }
    if(prev0==NULL)
        hashTable[oldindex] = curr0->next;
    else
        prev0->next = curr0->next;
    if(prev1==NULL){
        Node new = (Node)malloc(sizeof(struct Node));
        new->key = newKey;
        new->next = curr1;
        hashTable[newindex] = new; 
    }else{
        Node new = (Node)malloc(sizeof(struct Node));
        new->key = newKey;
        new->next = curr1;
        prev1->next = new;
    }
    free(curr0);
    printf("%d %d\n",oldindex,pos);
}

void printElementsInChain(Node* hashTable,int index){
    Node node = hashTable[index];
    if(node==NULL){
        printf("-1\n");
        return;
    }
    while(node){
        printf("%d ",node->key);
        node = node->next;
    }
    printf("\n");
}

int main(){
    int size;
    scanf("%d",&size);
    Node hashTable[size];
    for(int i=0;i<size;i++)
        hashTable[i] = NULL;
    char choice;
    do
    {
        scanf("%c",&choice);
        if(choice=='a'){
            int key;
            scanf("%d",&key);
            insert(hashTable,size,key);
        }
        else if(choice=='b'){
            int key;
            scanf("%d",&key);
            search(hashTable,size,key);
        }
        else if(choice=='c'){
            int key;
            scanf("%d",&key);
            delete(hashTable,size,key);
        }
        else if(choice=='d'){
            int old, new;
            scanf("%d %d",&old,&new);
            update(hashTable,size,old,new);
        }
        else if(choice=='e'){
            int index;
            scanf("%d",&index);
            printElementsInChain(hashTable,index);
        }
    } while (choice!='f');
    
}