
typedef struct
{
	int x;
	int y;
}PosType;

typedef struct
{
	int ord;
	PosType seat;
	int di;
}SElemType;

#include "c1.h"
#include "c3.h"

int maze[100][100];
int curstep;

Status InitStack(SqStack *S)
{
    (*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

Status Push(SqStack *S,SElemType e)
{
	if((*S).top-(*S).base>(*S).stacksize)
	{
		(*S).base = (SElemType*)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)
		    exit(-1);
	}
	*(*S).top++=e;
	return 1;
}

Status Pop(SqStack *S,SElemType *e)
{
	if((*S).base == (*S).top)
	    return 0;
	*e=*--(*S).top;
	return 1;
}


Status Pass(PosType b)
{
	if(maze[b.x][b.y]==0)
	    return 1;
	else
	    return 0;
}

Status FootPrint(PosType a)
{
	maze[a.x][a.y]=1;
	return 1;
}

PosType NextPos(PosType c,int di)
{
    PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}};
    c.x+=direc[di].x;
    c.y+=direc[di].y;
	return c;
}

Status MarkPrint(PosType e)
{
	maze[e.x][e.y]=-1;
	return 1;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
    	return 1;
	else
    	return 0;
}

Status MazePath(PosType begin,PosType end)
{
    SqStack s;
    InitStack(&s);
    PosType curpos;
    SElemType e;
    curpos = begin;
    do
    {
        if(Pass(curpos))
        {
            e.ord = curstep;
            e.seat.x = curpos.x;
            e.seat.y = curpos.y;
            e.di = 0;
            curstep++;
            Push(&s,e);
            if(curpos.x == end.x&&curpos.y == end.y)
                return 1;
            curpos = NextPos(curpos,e.di);
        }
        else
        {
            if(!StackEmpty(s))
            {

                Pop(&s,&e);
                curstep--;
                while(e.di==3&&!StackEmpty(s))
               {
                    MarkPrint(e.seat);
                    Pop(&s,&e);
               }
               if(e.di<3)
               {
                   e.di++;
                   Push(&s,e);
                   curstep++;
                   curpos = NextPos(e.seat,e.di);
               }
            }
        }
    }while(!StackEmpty(s));
    return 0;
}

void print(int m,int n)
{
	int i,j;
    for(i=0;i<m;i++)
	{
	    for(j=0;j<n;j++)
	    printf("%d ",maze[i][j]);
	    printf("\n");
	}
}

int main(int argc,char** argv)
{
	PosType begin,end;
	int i,j,m,n,x,y;
	printf("Please input the maze,and input row and array first\n");
	// 0 denotes  wall and 1 denotes  road
	scanf("%d %d",&m,&n);
	for(i=0;i<m;i++)
	{
		maze[i][0]=0;
		maze[i][n-1]=0;
	}

	for(j=0;j<n;j++)
	{
		maze[0][j]=0;
		maze[m-1][j]=0;
	}

	for(i=1;i<m-1;i++)
	    for(j=1;j<n-1;j++)
	    {
	    	maze[i][j]=1;
		}

	printf("Please input the number of walls");
	scanf("%d",&j);
	for(i=0;i<j;i++)
	{
		scanf("%d %d",&x,&y);
		maze[x][y] = 0;
	}

	printf("The maze is like follows\n");
    print(m,n);

	printf("Please input the entry");
	scanf("%d %d",&begin.x,&begin.y);
	printf("Please input the end");
	scanf("%d %d",&end.x,&end.y);
	if(MazePath(begin,end))
	{
		printf("This maze has one way  out\n");
		print(m,n);
	}
	else
	{
		printf("There is no way out");
	}

		return 0;
}
