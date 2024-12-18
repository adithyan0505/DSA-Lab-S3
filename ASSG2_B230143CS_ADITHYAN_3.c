#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct TreeNode{
    int val,height;
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

Node new(int val){
    Node newNode = (Node)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->height = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
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

void pexp(Node root)
{
    if(root->left==NULL && root->right!=NULL)
        printf("( ) ");
	if(root->left)
	{
        printf("( ");
		printf("%d ",(root->left)->val);
		pexp(root->left);
        printf(") ");
	}
	if(root->right)
	{
        printf("( ");
		printf("%d ",(root->right)->val);
		pexp(root->right);
        printf(") ");
	}
    if(root->left!=NULL && root->right==NULL)
        printf("( ) ");
}

Node Insert(Node root,int val)
{
    if(root==NULL){
        Node new = (Node)malloc(sizeof(struct TreeNode));
        new->val = val;
        new->left = new->right = NULL;
        new->height = 0;
        return new;
    }
    else if(root->val > val){
        root->left = Insert(root->left,val);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor > 1 || balance_factor < -1)
        {
            if(root->left->val > val) //left-subtree of left-child: right-rotation (outside case)
                return rotateRight(root);
            else        //right subtree of left-child: double rotation (inside case)
            {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    else{
        root->right = Insert(root->right,val);
        int balance_factor = height(root->left) - height(root->right);
        if(balance_factor > 1 || balance_factor < -1)
        {
            if(root->right->val < val) //right-subtree of right-child: right-rotation (outside case)
                return rotateLeft(root);
            else        //left subtree of right-child: double rotation (inside case)
            {
                root->right = rotateRight(root->right); //
                return rotateLeft(root);
            }
        }
        root->height = max(height(root->left),height(root->right)) + 1;
    }
    return root;
}

Node AVL_SeqInsert(Node root){
    char ch=getchar();
    while(ch!='\n')
    {
        int num = 0, flag = 0;
        while(isdigit(ch)){
            num *= 10;
            num += (ch-'0');
            flag = 1;
            ch = getchar();
        }
        if(flag)
            root = Insert(root,num);
        else
            ch = getchar();
    }
    printf("%d ",root->val);
    pexp(root);
    printf("\n");
    return root;
}

Node successor(Node root,int val){
    Node succ = NULL;
    int flag = 0;
    while(root!=NULL){
        if(root->val > val){
            succ = root;
            root = root->left;
        }
        else if(root->val < val)
            root = root->right;
        else{
            if(root->right){
                succ = root->right;
                while(succ->left)
                    succ = succ->left;
            }
            flag = 1;
            break;
        }
    }
    if(!flag)
        succ = NULL;
    return succ;
}

Node predecessor(Node root, int val){
	Node pred = NULL;
    int flag = 0;
    while(root!=NULL){
        if(root->val > val)
            root = root->left;
        else if(root->val < val){
            pred = root;
            root = root->right;
        }
        else{
            if(root->left){
                pred = root->left;
                while(pred->right)
                    pred = pred->right;
            }
            flag = 1;
            break;
        }
    }
    if(!flag)
        pred = NULL;
    return pred;
}

Node UpperBound(Node root,int key){
    Node ub = NULL;
    while(root!=NULL){
        if(root->val > key)
        {
            ub = root;
            root = root->left;
        }
        else if(root->val < key)
            root = root->right;
        else{
            ub = root;
            break;
        }
    }
    return ub;
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

void Preorder(Node root){
    if(root){
        printf("%d ",root->val);
        Preorder(root->left);
        Preorder(root->right);
    }
}

Node AVL_RangeDelete(Node root,int n1,int n2){
    if(root==NULL){
        printf("-1\n");
        return NULL;
    }
    int total = 0;
    Node ub = UpperBound(root,n1);
    Node next=ub;
    if(ub)
        n1 = ub->val;
    while(n1 <= n2 && next!=NULL){  //include case where root is to be deleted and no succ
        next = successor(root,n1);
        root = Delete(root,n1);
        total++;
        if(next)
            n1 = next->val;
    }
    if(!total)
        printf("-1\n");
    else{
        printf("%d ",total);
        Preorder(root);
        printf("\n");
    }
    return root;
}

void Path(Node root,int val){
    while(root){
        if(root->val > val)
        {
            printf("%d ",root->val);
            root = root->left;
        }
        else if(root->val < val)
        {
            printf("%d ",root->val);
            root = root->right;
        }
        else{
            printf("%d",root->val);
            return;
        }
    }
}

void AVL_SuccessorPath(Node root,int n){
    Node succ = successor(root,n);
    if(succ==NULL)
        printf("%d\n",root->height);
    else{
        Path(root,succ->val);
        printf("\n");
    }
    return;
}

void KeySum(Node root,int* sum){
    if(root){
        (*sum) += root->val;
        KeySum(root->left,sum);
        KeySum(root->right,sum);
    }
    return;
}

void AVL_SubtreeSum(Node node,int n){
    while(node){
        if(node->val > n)
            node = node->left;
        else if(node->val < n)
            node = node->right;
        else
            break;
    }
    if(node==NULL)
        printf("-1\n");
    else{
        int sum = 0;
        KeySum(node,&sum);
        printf("%d %d ",sum,node->val);
        pexp(node);
        printf("\n");
    }
}

void AVL_FindClosest(Node root,int val){
    Node succ = successor(root,val);
    Node pred = predecessor(root,val);
    if(succ==NULL && pred==NULL)
        printf("-1\n");
    else if(succ==NULL)
        printf("%d\n",pred->val);
    else if(pred == NULL)
        printf("%d\n",succ->val);
    else{
        if((succ->val - val) < (val - pred->val))
            printf("%d\n",succ->val);
        else
            printf("%d\n",pred->val);
    }
    return;
}

int main(){
    Node root = NULL;
    Node stack[1000];
    int top = -1;
    char ch;
    do
    {
        ch=getchar();
        int num=0;
        int flag = 0;
        while (isdigit(ch))
        {
            num *= 10;
            num += (ch-'0');
            ch=getchar();
            flag=1;
        }
        if(flag==1)
        {
            if(ch==' ')
                ch=getchar();
            if(root==NULL) root = new(num);
            else if(root->left==NULL)
            {
                Node left = new(num);
                root->left = left;
                root = root->left;
            }
            else if(root->right==NULL)
            {
                Node right = new(num);
                root->right = right;
                root = root->right;
            }
        }
        if(ch=='(')
        {
            top++;
            stack[top]=root;
            ch=getchar();
        }
        else if(ch==')')
        {
            if(top>-1)
                root = stack[top];
            root->height = max(height(root->left),height(root->right))+1;
            top--;
            ch=getchar();
        }
    } while ((top!=-1 || root->right==NULL) && ch!='\n');
    char choice;
    do
    {
        scanf("%c",&choice);
        if(choice=='a')
            root = AVL_SeqInsert(root);
        else if(choice=='b'){
            int n1,n2;
            scanf("%d %d",&n1,&n2);
            root = AVL_RangeDelete(root,n1,n2);
        }
        else if(choice=='c'){
            int n;
            scanf("%d",&n);
            AVL_SuccessorPath(root,n);
        }
        else if(choice=='d'){
            int n;
            scanf("%d",&n);
            AVL_SubtreeSum(root,n);
        }
        else if(choice=='e'){
            int n;
            scanf("%d",&n);
            AVL_FindClosest(root,n);
        }
    } while (choice!='g');
    return 0;
}