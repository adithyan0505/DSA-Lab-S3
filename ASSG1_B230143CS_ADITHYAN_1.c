#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree{
    int val;
    struct BinaryTree *left, *right;
}* Node;

struct QSNode {
    Node node;
    struct QSNode* next;
};

struct Queue {
    struct QSNode* front;
    struct QSNode* rear;
};

struct Stack {
    struct QSNode* top;
};

Node newNode(int);
int findPos(int*, int, int);
Node buildTree(int*, int, int*, int);
void Postorder(Node);
void enqueue(struct Queue*, Node);
Node dequeue(struct Queue*);
void push(struct Stack*, Node);
Node pop(struct Stack*);
void zig_zag(Node);
void LevelMax(Node);
void Diameter(Node);
int RightLeafSum(Node);

int main()
{
    int n;
    scanf("%d",&n);
    int pre[n], in[n];
    for(int i = 0;i < n;i++)
        scanf("%d",&in[i]);
    for(int i = 0;i < n;i++)
        scanf("%d",&pre[i]);
    Node root = buildTree(pre,n,in,n);
    char ch;
    do
    {
        scanf("%c",&ch);
        if(ch=='p')
        {
            Postorder(root);
            printf("\n");
        }
        else if(ch=='z')
        {
            zig_zag(root);
            printf("\n");
        }
        else if(ch=='m')
        {
            LevelMax(root);
            printf("\n");
        }
        else if(ch=='d')     //wrong test case??
        {
            Diameter(root);
            printf("\n");
        }
        else if(ch=='s')
        {
            int sum = RightLeafSum(root);
            printf("%d\n",sum);
        }
    } while (ch!='e');
    return 0;
}

Node newNode(int val)
{
    Node new = (Node)malloc(sizeof(struct BinaryTree));
    new->val = val;
    new->right = new->left = NULL;
    return new;
}

int findPos(int* arr, int size, int key) {
    int pos;
    for (pos = 0; pos < size; pos++) {
        if (arr[pos] == key)
            break;
    }
    return pos;
}

Node buildTree(int* pre, int preSize, int* in, int inSize) {
    Node root = newNode(pre[0]);
    int index = findPos(in, inSize, pre[0]);
    if (index)
        root->left = buildTree(pre + 1, preSize - 1, in, index);
    if (inSize - index - 1)
        root->right = buildTree(pre + index + 1, preSize - index - 1, in + index + 1, inSize - index - 1);
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

void enqueue(struct Queue* q, Node node) {
    struct QSNode* newNode = (struct QSNode*)malloc(sizeof(struct QSNode));
    newNode->node = node;
    newNode->next = NULL;
    if (q->front == NULL)
        q->front = q->rear = newNode;
    else {
        (q->rear)->next = newNode;
        q->rear = newNode;
    }
}

Node dequeue(struct Queue* q) {
    if (q->front == NULL)
        return NULL;
    struct QSNode* temp = q->front;
    Node node = temp->node;
    q->front = temp->next;
    free(temp);
    return node;
}

void push(struct Stack* s, Node node) {
    struct QSNode* newNode = (struct QSNode*)malloc(sizeof(struct QSNode));
    newNode->next = s->top;
    newNode->node = node;
    s->top = newNode;
}

Node pop(struct Stack* stack) {
    if (stack->top == NULL)
        return NULL;
    struct QSNode* temp = stack->top;
    Node node = temp->node;
    stack->top = (stack->top)->next;
    free(temp);
    return node;
}

void zig_zag(Node root)
{
    if(root == NULL)
        return;
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->top = NULL;
    enqueue(q, root);
    Node node;
    int size = 1, level = 0;
    while (q->front != NULL) {
        while (size) {
            node = dequeue(q);
            size--;
            printf("%d ",node->val);
            if (level % 2) {
                if (node->left)
                    push(s, node->left);
                if (node->right)
                    push(s, node->right);
            } else {
                if (node->right)
                    push(s, node->right);
                if (node->left)
                    push(s, node->left);
            }
        }
        while (s->top) {
            size++;
            enqueue(q, pop(s));
        }
        level++;
    }
    free(s);
    free(q);
    return;
}

void LevelMax(Node root)
{
    if(root == NULL)
        return;
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    enqueue(q,root);
    int size = 1, max, n;
    while(q->front != NULL)
    {
        n = size;
        max = 0;
        for(int i = 0;i < n;i++)
        {
            Node node = dequeue(q);
            size--;
            if(node->val > max)
                max = node->val;
            if(node->left)
            {
                enqueue(q,node->left);
                size++;
            }
            if(node->right)
            {
                enqueue(q,node->right);
                size++;
            }
        }
        printf("%d ",max);
    }
    return;
}

int maxh(Node root,int* d)
{
    if(!root)
        return 0;
    int lh = maxh(root->left,d);
    int rh = maxh(root->right,d);
    if(*d < lh+rh)
        *d = lh+rh;
    if(lh > rh)
        return 1 + lh;
    return 1 + rh;
}

void Diameter(Node root)
{
    int longest_path = 0;
    maxh(root,&longest_path);
    int diameter = longest_path + 1;
    printf("%d",diameter);
}

int RightLeafSum(Node root)
{
    if(!root)
        return 0;
    int sum = 0;
    if(root->right && root->right->left == NULL && root->right->right == NULL)
        sum += (root->right)->val;
    sum += RightLeafSum(root->left) + RightLeafSum(root->right);
    return sum;
}