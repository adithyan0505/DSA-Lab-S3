#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int key, val, height;
    struct TreeNode *left, *right;
}* Node;

int max(int a,int b)
{
    if(a > b)
        return a;
    return b;
}

int height(Node root)
{
    if(root==NULL)
        return -1;
    return root->height;
}

Node rotateRight(Node root)
{
    Node new_root = root->left;
    root->left = root->left->right; //T2
    new_root->right = root;
    root->height = max(height(root->left),height(root->right)) + 1;
    new_root->height = max(height(new_root->left),root->height) + 1;
    return new_root;
}

Node rotateLeft(Node root)
{
    Node new_root = root->right;
    root->right = root->right->left;
    new_root->left = root;
    root->height = max(height(root->left),height(root->right)) + 1;
    new_root->height = max(height(new_root->left),root->height) + 1;
    return new_root;
}

Node Insert(Node root,int key,int val){
    if(root==NULL){
        Node new = (Node)malloc(sizeof(struct TreeNode));
        new->key = key;
        new->val = val;
        new->left = new->right = NULL;
        new->height = 0;
        return new;
    }
    else if(root->key > key){
        root->left = Insert(root->left,key,val);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor == 2 || balance_factor == -2)
        {
            if(root->left->key > key) //left-subtree of left-child: right-rotation (outside case)
                return rotateRight(root);
            else        //right subtree of left-child: double rotation (inside case)
            {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    else if(root->key < key){
        root->right = Insert(root->right,key,val);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor == 2 || balance_factor == -2)
        {
            if(root->right->key < key) //right-subtree of right-child: right-rotation (outside case)
                return rotateLeft(root);
            else        //left subtree of right-child: double rotation (inside case)
            {
                root->right = rotateRight(root->left);
                return rotateLeft(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    else
        root->val = val;
    return root;
}

void Display(Node root){
    if(root){
        Display(root->right);
        printf("%d ",root->key);
        Display(root->left);
    }
}

void Empty(Node root){
    if(root==NULL)
        printf("1\n");
    else
        printf("0\n");
}

Node Find(Node root,int key)
{
    while(root)
    {
        if(root->key==key)
            return root; 
        else if(root->key > key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL; 
}

void Size(Node root,int* s)
{
    if(root){
        Size(root->left,s);
        Size(root->right,s);
        (*s)++; 
    }
}

Node UpperBound(Node root,int key){
    Node ub = NULL;
    while(root!=NULL){
        if(root->key > key)
        {
            ub = root;
            root = root->left;
        }
        else if(root->key < key)
            root = root->right;
        else{
            ub = root;
            break;
        }
    }
    return ub;
}

int main(){
    char ch;
    int key,val;
    Node root = NULL;
    do
    {
        scanf("%c",&ch);
        if(ch=='i'){
            scanf("%d %d",&key,&val);
            root = Insert(root,key,val);
        }
        else if(ch=='d'){
            if(root==NULL)
                printf("-1\n");
            else{
                Display(root);
                printf("\n");
            }
        }
        else if(ch=='e')
            Empty(root);
        else if(ch=='f'){
            scanf("%d",&key);
            Node found = Find(root,key);
            if(found==NULL)
                printf("-1\n");
            else
                printf("%d %d\n",found->key,found->val);
        }
        else if(ch=='s'){
            int s = 0;
            Size(root,&s);
            printf("%d\n",s);
        }
        else if(ch=='u'){
            scanf("%d",&key);
            Node ub = UpperBound(root,key);
            if(ub==NULL)
                printf("-1\n");
            else
                printf("%d %d\n",ub->key,ub->val);
        }
    } while (ch!='t');
    
}