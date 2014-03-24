#include<stdio.h>

#include"stringhash.h"
#include"error.h"
#include"list.h"

typedef union hello{
	int a;
	char b;
	char *c;
	int *d;
}HELLO;

void sumprint(HELLO a, HELLO b)
{
	printf("%d\n",a.a+b.a);
}

HELLO newHello()
{
	HELLO temp;
	temp.a = 10;
	return temp;
}

int main()
{
	HELLO a,b,c;
	a.a = 4;
	int *x = &a.a;
	a.b = 'a';
	a.c = "hihi";

	*x = 12;

	LISTptr li = newList();

	int k;
	for(k =0 ; k < 10; k++)
	{
		listPushEnd(li,(ELEMENT)k);
	}
	
	HELLO hhh = newHello();

//	printf("%d\n",a);
//	printf("%d\n",sizeof(HELLO));
//	printf("%d\n",hhh.a);
//	sumprint(a,b);

	STRINGHASHptr hello = newStringHash();
//	stringStore(hello,"helloworld",newStore());

	stringStore(hello,"hihi",(ELEMENT)4);
	printf("hello: %d\n",stringLoad(hello,"hihi"));

//	printf("%d\n",stringIsIn(hello,"helloworld"));
	printf("%d\n",li->listsize);
	printf("dd%d\n",listGetFront(li));
	int* ele;
	listIter(li,ele)
	{
		printf("%d\n",*ele);
	}

	error("helloworld");
}
