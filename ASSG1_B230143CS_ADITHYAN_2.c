#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinarySearchTree{
    int modelno;
    char name[30];
    int price;
    struct BinarySearchTree *left, *right, *parent;
}* Node;

Node Create_Node(int,char*,int);
Node Add(Node,Node);
Node Search(Node,int);
Node Delete(Node,Node);
void Inorder(Node);
void Preorder(Node);
void Postorder(Node);
void Modify(Node,int,int);

int main()
{
    char ch;
    int price, model;
    char name[30];
    Node root = NULL;
    do
    {
        scanf("%c",&ch);
        if(ch=='a')
        {
            scanf("%d %s %d",&model,name,&price);
            root = Add(root,Create_Node(model,name,price));
        }
        else if(ch=='d')
        {
            scanf("%d",&model);
            Node target = Search(root,model);
            if(target)
            {
                printf("%d %s %d\n",target->modelno,target->name,target->price);
                root = Delete(root,target);
            }
            else
                printf("-1\n");
        }
        else if(ch=='s')
        {
            scanf("%d",&model);
            Node target = Search(root,model);
            if(target)
                printf("%d %s %d\n",target->modelno,target->name,target->price);
            else
                printf("-1\n");
        }
        else if(ch=='i')
            Inorder(root);
        else if(ch=='p')
            Preorder(root);
        else if(ch=='t')
            Postorder(root);
        else if(ch=='m')
        {
            scanf("%d %d",&model,&price);
            Modify(root,model,price);
        }
    } while (ch!='e');
    return 0;
}

Node Create_Node(int model_number,char* model_name,int price)
{
    Node new = (Node)malloc(sizeof(struct BinarySearchTree));
    new->modelno = model_number;
    strcpy(new->name,model_name);
    new->price = price;
    new->left = new->right = new->parent = NULL;
    return new;
}

Node Add(Node root,Node new)
{
    if(!root)
        root = new;
    else if(new->modelno > root->modelno)
    {
        root->right = Add(root->right,new);
        (root->right)->parent = root;
    }
    else
    {
        root->left = Add(root->left,new);
        (root->left)->parent = root;
    }
    return root;
}

Node Search(Node root,int model_number)
{
    if(!root || root->modelno == model_number)
        return root;
    else if(root->modelno > model_number)
        return Search(root->left,model_number);
    else
        return Search(root->right,model_number);
}

Node Delete(Node root,Node target)
{
    Node right = target->right;
    if(right)
    {
        while(right->left)
            right = right->left;
        target->modelno = right->modelno;
        target->price = right->price;
        strcpy(target->name,right->name);
        target->right = Delete(target->right,right);
    }
    else
    {
        Node temp = target->left;
        if(temp)
            temp->parent = temp->parent->parent;
        if(target != root)
        {
            if(target->parent->modelno > target->modelno)
                target->parent->left = temp;
            else
                target->parent->right = temp;
        }
        else
            root = root->left;
        free(target);
    }
    return root;
}

void Inorder(Node root)
{
    if(root)
    {
        Inorder(root->left);
        printf("%d %s %d\n",root->modelno,root->name,root->price);
        Inorder(root->right);
    }
}

void Preorder(Node root)
{
    if(root)
    {
        printf("%d %s %d\n",root->modelno,root->name,root->price);
        Preorder(root->left);
        Preorder(root->right);
    }
}

void Postorder(Node root)
{
    if(root)
    {
        Postorder(root->left);
        Postorder(root->right);
        printf("%d %s %d\n",root->modelno,root->name,root->price);
    }
}

void Modify(Node root,int model_number,int new_price)
{
    Node node = Search(root,model_number);
    if(node)
    {
        node->price = new_price;
        printf("%d %s %d\n",node->modelno,node->name,node->price);
    }
    else
        printf("-1\n");
    return;
}