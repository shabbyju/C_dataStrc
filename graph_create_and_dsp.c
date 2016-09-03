
#include "c1.h"
#include "tree.h"
#define MAX_TREE_SIZE
typedef char TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];
typedef struct QNode
 {
   BiTree data;
   struct QNode *next;
 }QNode,*QueuePtr;

typedef struct
 {
   QueuePtr front,rear;
 }LinkQueue;

Status InitTree(BiTree *T)
{
    *T = NULL;
    return 1;
}

Status CreateBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    if(ch == ' ')
        *T = NULL;
        else
        {
            *T = (BiTree )malloc(sizeof(BiTNode));
            if(!*T)
            {
                exit(-2);
            }
            (*T)->data = ch;
            CreateBiTree(&(*T)->lchild);
            CreateBiTree(&(*T)->rchild);
        }
    return 1;
}

int BiTreeEmpty(BiTree T)
{
    if(T)
        return 0;
    else
        return 1;
}

TElemType Root(BiTree T)
{
    if(BiTreeEmpty(T))
        return 0;
    else
    return T->data;
}


Status PostOrderTraverse(BiTree T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c ",T->data);
    }
    return 1;
}
 Status InitQueue(LinkQueue *Q)
 { 
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
   return OK;
 }

Status EnQueue(LinkQueue *Q,BiTree e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QueuePtr));
    if(!p)
        exit(-1);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return 1;
}

Status DeQueue(LinkQueue *Q,BiTree* e)
{
    QueuePtr p;
    if(Q->front ==Q->rear)
    {
        return -1;
    }
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return 1;
}

Status QueueEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
        return 1;
    else
        return 0;
}
void LevelOrderTraverse(BiTree T)
{
   LinkQueue q;
   BiTree a;
   a = (BiTree*)malloc(sizeof(BiTNode));
   if(T)
   {
       InitQueue(&q);
       EnQueue(&q,T);
       while(!QueueEmpty(q))
       {
           DeQueue(&q,&a);
           printf(" %c ",a->data);
           if(a->lchild!=NULL) EnQueue(&q,a->lchild);
           if(a->rchild!=NULL) EnQueue(&q,a->rchild);
       }
       printf("\n");
   }
}

int main()
{
    int i;
    BiTree T,c,q;
    TElemType e1,e2;
    InitTree(&T);
    e1 = Root(T);
    if(e1!=NULL)
        printf("The root is %c",e1);
    printf("Please input preorder BiTree\n");
    CreateBiTree(&T);
    printf("PostOrder is:\n");
    PostOrderTraverse(T);
    LevelOrderTraverse(T);
    return 0;
}
