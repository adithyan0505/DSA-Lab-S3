#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Student{
    char first_name[30];
    char rollno[15];
    int age;
    struct Student* next;
}* Student;

void selectionSort(Student head,int* count){
    Student it;
    Student min;
    if(head)
        (*count)++;
    else{
        //(*count) = -1;
        return;
    }
    while(head && head->next){
        it = head->next;
        min = head;
        while(it!=NULL){
            if(strcmp(min->first_name,it->first_name) > 0)
                min = it;
            it = it->next;
        }
        if(min!=head){
            int temp_age = head->age;
            head->age = min->age;
            min->age = temp_age;
            char temp_name[30];
            strcpy(temp_name,head->first_name);
            strcpy(head->first_name,min->first_name);
            strcpy(min->first_name,temp_name);
            char temp_rollno[15];
            strcpy(temp_rollno,head->rollno);
            strcpy(head->rollno,min->rollno);
            strcpy(min->rollno,temp_rollno);
        }
        head = head->next;
        (*count)++;
    }
}

int getGroupIndex(Student stud){
    int ascii_sum = 0,length = strlen(stud->first_name);
    for(int i = 0;i < length;i++)
        ascii_sum += stud->first_name[i];
    int gi = (ascii_sum + stud->age) % 4;
    return gi;
}

int GroupIndexAndSplit(char* first_name,Student* H){
    int gi;
    for(gi = 0;gi<=3;gi++){
        Student student = H[gi];
        while(student != NULL){
            if(strcmp(first_name,student->first_name)==0){
                return gi;
            }
            student = student->next;
        }
    }
    return -1;
}

void Group_CountAndList(Student* H,int k){
    int count = 0;
    selectionSort(H[k],&count);
    printf("%d ",count);
    Student stud = H[k];
    while(stud){
        printf("%s ",stud->first_name);
        stud = stud->next;
    }
    printf("\n");
}

void Group_ListByBranch(Student* H,int m,char* branch){
    Student stud = H[m];
    int flag = 0;
    for(int i=0;i<2;i++)
        branch[i] = toupper(branch[i]);
    while(stud){
        if(strncmp(&stud->rollno[7],branch,2) == 0){
            flag = 1;
            printf("%s ",stud->first_name);
        }
        stud = stud->next;
    }
    if(!flag)
        printf("-1\n");
    else
        printf("\n");
}

void StudentDetails(Student* H,char* rollno){
    int found = 0;
    for(int gi=0;gi<=3;gi++){
        Student stud = H[gi];
        while(stud){
            if(strcmp(stud->rollno,rollno)==0){
                found = 1;
                printf("%s %d %s\n",stud->first_name,stud->age,&stud->rollno[7]);
                return;
            }
            stud = stud->next;
        }
    }
    if(!found)
        printf("-1\n");
}

void Group_TransferAllByBranch(Student* H,int source_m,int target_m,char* branch){
    int count = 0;
    Student source = H[source_m];
    Student target = H[target_m];
    for(int i=0;i<2;i++)
        branch[i] = toupper(branch[i]);
    while(source && strncmp(&source->rollno[7],branch,2) == 0){
        Student temp = source;
        source = source->next;
        H[source_m] = source;
        count++;
        temp->next = target;
        target = temp;
        H[target_m] = target;
    }
    while(source && source->next){
        if(strncmp(&source->next->rollno[7],branch,2) == 0){
            Student temp = source->next;
            source->next = source->next->next;
            count++;
            temp->next = target;
            target = temp;
        }
        source = source->next;
    }
    printf("%d\n",count);
}

int main(){
    int n;
    scanf("%d",&n);
    Student H[4] = {NULL,NULL,NULL,NULL};
    for(int i=0;i<n;i++){
        Student new = (Student)malloc(sizeof(struct Student));
        scanf("%s",new->first_name);
        scanf("%s",new->rollno);
        scanf("%d",&new->age);
        int group_index = getGroupIndex(new);
        new->next = H[group_index];
        H[group_index] = new;
    }
    char choice;
    do
    {
        scanf("%c",&choice);
        if(choice=='a'){
            char first_name[30];
            scanf("%s",first_name);
            printf("%d\n",GroupIndexAndSplit(first_name,H));
        }
        else if(choice=='b'){
            int k;
            scanf("%d",&k);
            Group_CountAndList(H,k);
        }
        else if(choice=='c'){
            int m;
            char branch[3];
            scanf("%d %s",&m,branch);
            Group_ListByBranch(H,m,branch);
        }
        else if(choice=='d'){
            char rollno[15];
            scanf("%s",rollno);
            StudentDetails(H,rollno);
        }
        else if(choice=='e'){
            int source_m, target_m;
            char branch[3];
            scanf("%d %d %s",&source_m,&target_m,branch);
            Group_TransferAllByBranch(H, source_m, target_m, branch);
        }
    } while (choice!='f');
}