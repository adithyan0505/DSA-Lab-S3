#include <stdio.h>

int parent(int i){
    return (i-1)/2;
}

void swap(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void HeapifyUP(int* heap,int size){
    int i = size-1;
    while((i != 0)&&(heap[parent(i)] < heap[i])){
        swap(&heap[parent(i)],&heap[i]);
        i = parent(i);
    }
}

void Insert(int* heap,int size,int key){
    heap[size-1] = key;
    HeapifyUP(heap,size);
}

int FindMax(int* heap){
    return heap[0];
}

void HeapifyDown(int* heap,int size,int i){
    int largest = i;
    int left = 2*i+1, right = 2*i+2;
    if((left < size) && (heap[largest] < heap[left]))
        largest = left;
    if((right < size) && (heap[largest] < heap[right]))
        largest = right;
    if(largest != i){
        swap(&heap[largest],&heap[i]);
        HeapifyDown(heap,size,largest);
    }

}

void LevelOrder(int* heap,int size){
    printf("%d ",heap[0]);
    for(int i=0;i <= (size-1)/2;i++){
        int left = 2*i+1, right = 2*i+2;
        if(left < size)
            printf("%d ",heap[left]);
        if(right < size)
            printf("%d ",heap[right]);
    }
    printf("\n");
}

void ExtractMax(int* heap,int size){
    swap(&heap[0],&heap[size-1]);
    HeapifyDown(heap,size-1,0);
    printf("%d ",heap[size-1]);
    LevelOrder(heap,size-1);
}

void kthLargest(int* heap,int size,int k){
    if(k > size){
        printf("-1\n");
        return;
    }
    int array[size];
    for(int i=0;i<size;i++)
        array[i] = heap[i];
    int temp_size = size;
    while(--k){
        swap(&array[0],&array[temp_size-1]);
        HeapifyDown(array,--temp_size,0);
    }
    printf("%d\n",array[0]);
}

void DeleteKey(int* heap,int* size,int key){
    int i;
    for(i = 0;i < (*size);i++){
        if(heap[i] == key)
            break;
    }
    if(i == (*size)){
        printf("-1\n");
        return;
    }
    swap(&heap[i],&heap[(*size)-1]);
    HeapifyDown(heap,--(*size),i);
    if(*size == 0){
        printf("0\n");
        return;
    }
    LevelOrder(heap,*size);
}

void ReplaceKey(int* heap,int size,int old_val,int new_val){
    int i;
    for(i = 0;i < size;i++){
        if(heap[i] == old_val)
            break;
    }
    if(i == size){
        if(old_val > new_val)
            printf("%d\n",old_val-new_val);
        else
            printf("%d\n",new_val-old_val);
        return;
    }
    heap[i] = new_val;
    if(old_val > new_val)
        HeapifyDown(heap,size,i);
    else{
        while((i != 0)&&(heap[parent(i)] < heap[i])){
            swap(&heap[parent(i)],&heap[i]);
            i = parent(i);
        }
    }
    LevelOrder(heap,size);

}

int main(){
    char ch;
    int key;
    int heap[200];
    int size = 0;
    do
    {
        scanf("%c",&ch);
        if(ch=='a'){
            scanf("%d",&key);
            size++;
            Insert(heap,size,key);
        }
        else if(ch=='b'){
            if(!size)
                printf("-1\n");
            else
                printf("%d\n",FindMax(heap));
        }
        else if(ch=='c'){
            if(size==0)
                printf("-1\n");
            else{
                ExtractMax(heap,size);
                size--;
            }
        }
        else if(ch=='d'){
            int k;
            scanf("%d",&k);
            kthLargest(heap,size,k);
        }
        else if(ch=='e'){
            scanf("%d",&key);
            DeleteKey(heap,&size,key);
        }
        else if(ch=='f'){
            int new_key;
            scanf("%d %d",&key,&new_key);
            ReplaceKey(heap,size,key,new_key);
        }
    } while (ch!='g');
    
}