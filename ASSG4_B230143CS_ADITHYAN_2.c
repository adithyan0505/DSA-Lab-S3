#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct P{
    char name[30];
    int patient_id;
    int severity;
}* patient;

int parent(int i){
    return (i-1)/2;
}

void swap(patient* a,patient* b){
    patient temp = *a;
    *a = *b;
    *b = temp;
}

void HeapifyUP(patient* PQ,int size){
    int i = size-1;
    while((i != 0) && (PQ[parent(i)]->severity > PQ[i]->severity)){
        swap(&PQ[parent(i)],&PQ[i]);
        i = parent(i);
    }
}

void HeapifyDown(patient* PQ,int size,int i){
    int smallest = i;
    int left = 2*i+1, right = 2*i+2;
    if((left < size) && (PQ[smallest]->severity > PQ[left]->severity))
        smallest = left;
    if((right < size) && (PQ[smallest]->severity > PQ[right]->severity))
        smallest = right;
    if(smallest != i){
        swap(&PQ[smallest],&PQ[i]);
        HeapifyDown(PQ,size,smallest);
    }
}

void LevelOrder(patient* heap,int size){
    printf("%d ",heap[0]->patient_id);
    for(int i=0;i <= (size-1)/2;i++){
        int left = 2*i+1, right = 2*i+2;
        if(left < size)
            printf("%d ",heap[left]->patient_id);
        if(right < size)
            printf("%d ",heap[right]->patient_id);
    }
    printf("\n");
}

void AdmitPatient(patient* PQ,int* size,int p_id,int severity,char* name){
    patient new_patient = (patient)malloc(sizeof(struct P));
    new_patient->patient_id = p_id;
    new_patient->severity = severity;
    strcpy(new_patient->name,name);
    PQ[(*size)] = new_patient;
    HeapifyUP(PQ,++(*size));
    LevelOrder(PQ,*size);
}

void TreatPatient(patient* PQ,int size){
    swap(&PQ[0],&PQ[size-1]);
    HeapifyDown(PQ,size-1,0);
    printf("%d %s\n",PQ[size-1]->patient_id,PQ[size-1]->name);
}

void UpdateSeverity(patient* PQ,int size,int p_id,int new_severity){
    int i;
    for(i = 0;i < size;i++){
        if(PQ[i]->patient_id == p_id)
            break;
    }
    if(i == size){
        printf("-1\n");
        return;
    }
    int old_severity = PQ[i]->severity;
    PQ[i]->severity = new_severity;
    if(new_severity > old_severity)
        HeapifyDown(PQ,size,i);
    else{
        while((i != 0)&&(PQ[parent(i)]->severity > PQ[i]->severity)){
            swap(&PQ[parent(i)],&PQ[i]);
            i = parent(i);
        }
    }
    LevelOrder(PQ,size);
}

void QueryPatient(patient* PQ,int size,int p_id){
    int i;
    for(i = 0;i < size;i++){
        if(PQ[i]->patient_id == p_id)
            break;
    }
    if(i == size){
        printf("-1\n");
        return;
    }
    printf("%s %d\n",PQ[i]->name,PQ[i]->severity);
}

void FindMostSevere(patient* PQ,int size){
    if(size==0){
        printf("-1\n");
        return;
    }
    patient array[size];
    for(int i=0;i<size;i++)
        array[i] = PQ[i];
    int temp_size = size;
    for(int i=0;i<3;i++){
        if(!temp_size)
            break;
        printf("%d %s %d\n",array[0]->patient_id,array[0]->name,array[0]->severity);
        swap(&array[0],&array[temp_size-1]);
        HeapifyDown(array,--temp_size,0);
    }
}

int main(){
    char ch;
    int p_id, severity;
    char name[30];
    patient* PQ = (patient*)malloc(200*sizeof(patient));
    int size = 0;
    do
    {
        scanf(" %c",&ch);
        if(ch=='a'){
            scanf("%d %d %s",&p_id,&severity,name);
            AdmitPatient(PQ,&size,p_id,severity,name);
        }
        else if(ch=='b'){
            if(!size)
                printf("-1\n");
            else{
                TreatPatient(PQ,size);
                size--;
            }
        }
        else if(ch=='c'){
            int new;
            scanf("%d %d",&p_id,&new);
            UpdateSeverity(PQ,size,p_id,new);
        }
        else if(ch=='d'){
            scanf("%d",&p_id);
            QueryPatient(PQ,size,p_id);
        }
        else if(ch=='e'){
            FindMostSevere(PQ,size);
        }
    } while (ch!='g');
    
}