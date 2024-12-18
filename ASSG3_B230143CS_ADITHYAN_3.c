#include <stdio.h>
#define EMPTY -1

void LinearProbing(int* hashTable,int N,int* elements,int m){
    int collisions = 0;
    for(int i=0;i<m;i++){
        int key = elements[i];
        int initial_index = key % N;
        int j = 1;
        int index = initial_index;
        while(hashTable[index]!=EMPTY){
            index = (initial_index + j) % N;
            j++;
            collisions++;
        }
        hashTable[index] = key;
        printf("%d ",index);
    }
    printf("\n%d\n",collisions);
}

void QuadraticProbing(int* hashTable,int N,int* elements,int m){
    int collisions = 0;
    for(int i=0;i<m;i++){
        int key = elements[i];
        int initial_index = key % N;
        int j = 1;
        int index = initial_index;
        while(hashTable[index]!=EMPTY){
            index = (initial_index + j*j) % N;
            j++;
            collisions++;
        }
        hashTable[index] = key;
        printf("%d ",index);
    }
    printf("\n%d\n",collisions);
}

int primary_hash(int key,int N){
    return (key % N);
}

int isPrime(int p){
    for(int i = 2;i < p/2;i++){
        if(p%i == 0)
            return 0;
    }
    return 1;
}

int findPrime(int N){
    int p;
    for(p=N-1;p > 1;p--){
        if(isPrime(p))
            break;
    }
    return p;
}

int secondary_hash(int key,int N){
    int R = findPrime(N);
    return (R - (key % R));
}

void DoubleHashing(int* hashTable,int N,int* elements,int m){
    int collisions = 0;
    for(int i=0;i<m;i++){
        int key = elements[i];
        int index = key % N;
        int j = 1;
        int h1 = primary_hash(key,N);
        int h2 = secondary_hash(key,N);
        while(hashTable[index]!=EMPTY){
            index = (h1 + j * h2) % N;
            j++;
            collisions++;
        }
        hashTable[index] = key;
        printf("%d ",index);
    }
    printf("\n%d\n",collisions);
}

int main(){
    int N,m;
    scanf("%d %d",&N,&m);
    int elements[m];
    for(int i=0;i<m;i++)
        scanf("%d",&elements[i]);
    char choice;
    int hashTable[N];
    do
    {
        scanf("%c",&choice);
        for(int i=0;i<N;i++)
            hashTable[i] = EMPTY;
        if(choice=='a')
            LinearProbing(hashTable,N,elements,m);
        else if(choice=='b')
            QuadraticProbing(hashTable,N,elements,m);
        else if(choice=='c')
            DoubleHashing(hashTable,N,elements,m);
    } while (choice!='d');
    
}