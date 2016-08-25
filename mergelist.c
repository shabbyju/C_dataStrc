#include <iostream>
#include "c1.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList(SqList *L)
{
	(*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!(*L).elem)
	    exit(1);
	(*L).length = 0;
	(*L).listsize = 0;
	return 1;	 
}

Status ListInsert(SqList *L,int i,ElemType e)
{
	ElemType *newbase,*p,*q;
	
	if(i<1||i>(*L).length+1)
	{
		    return -1;
	}
	
	if((*L).length>=(*L).listsize)
	{
		newbase = (ElemType*)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
		    exit(-1);
		(*L).elem=newbase;
		(*L).listsize+=LISTINCREMENT;
	}
	q = (*L).elem+i-1;
	for(p=(*L).elem+(*L).length-1;p>=q;--p)
	{
		*(p+1) = *p;
	}
	*q = e;
	++(*L).length;
	return 1;
}

void print(ElemType *e)
{
	printf("%d",*e);
}
Status ListTraverse(SqList L,void(*vi)(ElemType*))
{
	ElemType *p;
	int i;
	p=L.elem;

   for(i=1;i<=L.length;i++)
	{
	    printf("--");
	    vi(p++);
	}
	printf("\n");
	return 1;
}

Status GetElem(SqList L,int i,ElemType *e)
{
	if(i<1||i>L.length)
	     exit(-1);
	*e = *(L.elem+i-1);
	return 1;
}

void MergeList(SqList La,SqList Lb,SqList *Lc)
{
	int i=1,j=1,k=0;
	int La_len,Lb_len;
	ElemType ai,bj;
	InitList(Lc);
	La_len = La.length;
	Lb_len = Lb.length;
	printf("%d   %d",La_len,Lb_len);
    while(i<=La_len&&j<=Lb_len)
    {
    	GetElem(La,i,&ai);
    	GetElem(Lb,j,&bj);
    	if(ai<=bj)
    	{
    		ListInsert(Lc,++k,ai);
    		++i;
		}
		else
		{
			ListInsert(Lc,++k,bj);
			++j;
		}
	}
	
	while(i<=La_len)
	{
	
		GetElem(La,i++,&ai);
		ListInsert(Lc,++k,ai);
	}
	
	while(j<=Lb_len)
	{
		GetElem(Lb,j++,&bj);
		ListInsert(Lc,++k,bj);
	}


}
/*
int main(int argc, char** argv) {
    SqList La,Lb;
    Status i;
    int j;
    i = InitList(&La);
    printf("%d\n",i);
    if (i==1) {
             for(j=1;j<=5;j++)
              i = ListInsert(&La,j,2*j);
          }
    printf("La==");
    ListTraverse(La);
	return 0;
}*/


int main(int argc,char** argv)
{
	SqList La,Lb,Lc;
	int i,j,a[4]={1,2,3,4},b[7]={5,6,7,8,9,10,11};
	InitList(&La);
	for(j=1;j<=4;j++)
	{
		ListInsert(&La,j,a[j-1]);
	}
	printf("La==\n");
	ListTraverse(La,print);
	
	InitList(&Lb);
	for(j=1;j<=7;j++)
	    ListInsert(&Lb,j,b[j-1]);
	printf("Lb==\n");
	ListTraverse(Lb,print);
	MergeList(La,Lb,&Lc);
	printf("Lc===\n");
	ListTraverse(Lc,print);
	
	return 0;
}