#include "c1.h"
#define MAX_VEX 20
typedef char VertexType[MAX_VEX];
typedef struct ArcNode
{
    int adjvex;
    struct node *nextarc;
}ArcNode;

typedef struct VexNode
{
    VertexType vertex;
    ArcNode *firstedge;
}VertexNode,AdjList[MAX_VEX];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;
    int kind;
}ALGraph;

int LocateVex(ALGraph *G,VertexType u)
{
    int i;
    for(i=0;i<G->vexnum;i++)
        if(strcmp(u,G->vertices[i].vertex)==0)
           return i;
    return -1;
}

void Display(ALGraph *G)
{
    int i = 0;
    ArcNode *p;
    for(i=0;i<G->vexnum;i++)
    {
        p = G->vertices[i].firstedge;
       // printf("The adjvex is :%d",p->adjvex);
        printf("%s",G->vertices[i].vertex);
        while(p)
        {
            printf("->%s",G->vertices[p->adjvex].vertex);
            p=p->nextarc;
        }
        printf("\n");
    }
}

int create(ALGraph *G)
{
    int i,j,k,m;
    VertexType va,vb;
    ArcNode *p;
    printf("please input the number of vex and edge\n");
    scanf("%d %d",&G->vexnum,&G->arcnum);
    printf("please input vertex table\n");
    for(i=0;i<G->vexnum;i++)
    {
        fflush(stdin);
        printf("The vertex is:");
        scanf("%s",G->vertices[i].vertex);
        G->vertices[i].firstedge = NULL;
    }

    printf("please input the edge table\n");
    for(j=0;j<G->arcnum;j++)
    {
        printf("\ninput arc(vi-vj):");
        scanf("%s%s",&va,&vb);
        k = LocateVex(G,va);
        m = LocateVex(G,vb);
        printf("k,m is %d,%d",k,m);
        p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p)
            exit(-1);
        p->adjvex = m;
        p->nextarc = G->vertices[k].firstedge;
        G->vertices[k].firstedge = p;
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = k;
        p->nextarc = G->vertices[m].firstedge;
        G->vertices[m].firstedge = p;
    }

    return 0;
}

int main(int argc,char** argv)
{
    ALGraph g;
    create(&g);
    Display(&g);
    return 0;
}
