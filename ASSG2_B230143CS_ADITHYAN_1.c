#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int val;
    int height;
    struct TreeNode *left,*right;
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

Node Insert(Node root,int val,int* left_rotations,int* right_rotations)
{
    if(root==NULL){
        Node new = (Node)malloc(sizeof(struct TreeNode));
        new->val = val;
        new->left = new->right = NULL;
        new->height = 0;
        return new;
    }
    else if(root->val > val){
        root->left = Insert(root->left,val,left_rotations,right_rotations);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor == 2 || balance_factor == -2)
        {
            if(root->left->val > val) //left-subtree of left-child: right-rotation (outside case)
            {
                (*right_rotations)++;
                return rotateRight(root);
            }
            else        //right subtree of left-child: double rotation (inside case)
            {
                (*left_rotations)++; (*right_rotations)++;
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    else{
        root->right = Insert(root->right,val,left_rotations,right_rotations);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor == 2 || balance_factor == -2)
        {
            if(root->right->val < val) //right-subtree of right-child: right-rotation (outside case)
            {
                (*left_rotations)++;
                return rotateLeft(root);
            }
            else        //left subtree of right-child: double rotation (inside case)
            {
                (*left_rotations)++; (*right_rotations)++;
                root->right = rotateRight(root->left);
                return rotateLeft(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    return root;
}

void Postorder(Node root)
{
    if(root)
    {
        Postorder(root->left);
        Postorder(root->right);
        printf("%d ",root->val);
    }
}

int balanceFactor(Node root,int val)
{
    while(root)
    {
        if(root->val==val)
            return (height(root->left)-height(root->right)); 
        else if(root->val > val)
            root = root->left;
        else
            root = root->right;
    }
    return -1;
}

Node AVL_find(Node root,int key)
{
    while(root)
    {
        if(root->val==key)
            return root; 
        else if(root->val > key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

Node Delete(Node root,int val)
{
    if(root==NULL)
        return NULL;
    if(root->val > val)
        root->left = Delete(root->left,val);
    else if(root->val < val)
        root->right = Delete(root->right,val);
    else{
        if(root->left==NULL){
            Node temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right==NULL){
            Node temp = root;
            root = root->left;
            free(temp);
        }
        else{
            Node temp = root->right;
            while(temp->left)
                temp = temp->left;
            root->val = temp->val;
            root->right = Delete(root->right,temp->val);
        }
    }
    if(root==NULL)
        return NULL;

    root->height = 1 + max(height(root->left),height(root->right));
    int bf = height(root->left) - height(root->right);
    if(bf==2 && height(root->left->left)-height(root->left->right)>=0)
        return rotateRight(root);
    if(bf==2 && height(root->left->left)-height(root->left->right)<0){
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(bf==-2 && height(root->right->left)-height(root->right->right)<=0)
        return rotateLeft(root);
    if(bf==-2 && height(root->right->left)-height(root->right->right)>0){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void Ancestor(Node root,int val){
    if(root==NULL)
        return;
    if(root->val > val){
        Ancestor(root->left,val);
        printf("%d ",root->val);
    }
    else if(root->val < val){
        Ancestor(root->right,val);
        printf("%d ",root->val);
    }
    else
        printf("%d ",root->val);
    return;
}

int main()
{
    char ch;
    int val;
    int lR = 0, rR = 0;
    Node root = NULL;
    do{
        scanf("%c",&ch);
        if(ch=='i')
        {
            scanf("%d",&val);
            root = Insert(root,val,&lR,&rR);
        }
        else if(ch=='p')
        {
            Postorder(root);
            printf("\n");
        }
        else if(ch=='s')
            printf("%d %d\n",lR,rR);
        else if(ch=='b')
        {
            scanf("%d",&val);
            printf("%d\n",balanceFactor(root,val));
        }
        else if(ch=='f')
        {
            scanf("%d",&val);
            Node found = AVL_find(root,val);
            if(!found)
                printf("-1\n");
            else{
                Node temp = root;
                while(temp){
                    if(temp == found)
                    {
                        printf("%d\n",found->val);
                        break;
                    }
                    else if(temp->val > found->val)
                    {
                        printf("%d ",temp->val);
                        temp = temp->left;
                    }
                    else{
                        printf("%d ",temp->val);
                        temp = temp->right;
                    }
                }
            }
        }
        else if(ch=='d')
        {
            scanf("%d",&val);
            Node found = AVL_find(root,val);
            if(!found)
                printf("-1\n");
            else{
                Ancestor(root,found->val);
                root = Delete(root,found->val);
                printf("\n");
            }
        }
    } while (ch!='e');
    return 0;
}