#include <stdio.h>
#include <stdlib.h>
#include "c3.h"
#include "c1.h"

typedef int SElemType;
Status InitStack(SqStack *S)
{
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
	    exit(-1);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

Status Push(SqStack *S,SElemType e)
{
	if((*S).top-(*S).base>(*S).stacksize)
	{
		(*S).base=(SElemType*)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)
		{
		    exit(-1);	
		}
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize+=STACKINCREMENT;
	}
	*((*S).top)++=e;
	return 1;
}

Status Pop(SqStack *S,SElemType *e)
{
	if((*S).top==(*S).base)
	{
		return 0;
	}
	*e = *--(*S).top;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
		return 1;
    else
	   return 0;
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void conversion()
{
	SqStack s;
	unsigned n;
	SElemType e;
	InitStack(&s);
	printf("n=");
	scanf("%d",&n);
	
	while(n)
	{
		Push(&s,n%8);
		n/=8;
	}
	
	while(!StackEmpty(s))
	{
	    Pop(&s,&e);
	    printf("%d",e);
	}
	printf("\n");
	
}

int check()
{
	SqStack s;
	char ch[80],e,*p;
	int i;
	InitStack(&s);
	printf("Plase input your bracket expression");
	gets(ch);
	p=ch;

	while(*p)
	{
		switch(*p)
		{
			case '(':
			case '[':
				printf("==========\n");
				Push(&s,*p++);
				printf("%c",*p);
				break;
			case ')':
			case ']':
				if(!StackEmpty(s))
				{
			     	Pop(&s,&e);
			     	if(*p==')'&&e=='('||*p=="["&&e==']')
			     	    Pop(&s,&e);
			     	else
			     	{
			     		p++;
			     		break;
					}
				}
				else
				{
					printf("The left brakct is lost");
					exit(-1);
				}
			default:p++;
			
		}
		
	}
	if(StackEmpty(s))
	    printf("OK");
	else
	    printf("error");
	return 0;
}

int main(int argc, char *argv[]) {
//	conversion();
    check();
	return 0;
}