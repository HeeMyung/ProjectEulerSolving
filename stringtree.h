#ifndef __STRINGTREE_H_

#define __STRINGTREE_H_


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struct.h"
#define resolve(a) ((a >= 'a') ? (a - 'a') : (a - 'A'))

typedef ELEMENT STORE;

typedef struct StringTree{
	struct StringTree **next;
	STORE store;
	char check;
}STRINGTREE,*STRINGTREEptr,**STRINGTREElist;

STRINGTREEptr stringTree()
{
	STRINGTREEptr ret = (STRINGTREEptr)calloc(1,sizeof(STRINGTREE));
	ret->next = (STRINGTREElist)calloc(24,sizeof(STRINGTREEptr));
	ret->check = 0;
	return ret;
}

STRINGTREEptr stringSet(STRINGTREEptr tree, char* str);

char* change(char* string)	// 이 함수는 스트링의 맨 앞글자를 잘라낸 다음글자의 포인터를 린턴합니다.
{
	// 널 스트링 체크따위 안합니다.
	return &string[1];
}

STRINGTREEptr getTreeElement(STRINGTREEptr tree, char *str)
{
	if(*str == '\0')
	{
		return tree;
	}
	else
	{
		if( tree->next[resolve(*str)] == NULL)
			tree->next[resolve(*str)] = stringTree();
		return getTreeElement(tree->next[resolve(*str)],change(str));	// 다음 트리로 갑니다.
	}
}	// 트리의 지정된 엘리먼트를 리턴함

/*
STRINGTREEptr stringSet(STRINGTREEptr tree, char* str)
{
	STRINGTREEptr temp = getTreeElement(tree,str);
	temp->check = 1;
	return tree;
}
*/	// 왜 쓰는지 모르겠어서 주석처리 해 둡니다.


int stringIsIn(STRINGTREEptr tree, char *str)
{
	STRINGTREEptr temp = getTreeElement(tree,str);
	if(temp->check == 1)
		return 1;
	else 
		return 0;
}

STRINGTREEptr stringStore(STRINGTREEptr tree, char* str, STORE sto)
{
	STRINGTREEptr temp = getTreeElement(tree,str);
	temp->check = 1;
	temp->store = sto;
	return tree;
}	// 스트링 트리에 데이터를 저장합니다.

STRINGTREEptr stringDelete(STRINGTREEptr tree, char* str)
{
	STRINGTREEptr temp = getTreeElement(tree,str);
	temp->check = 0;
	return tree;
}

STORE stringLoad(STRINGTREEptr tree, char* index)
{
	STRINGTREEptr temp = getTreeElement(tree,index);
	if(temp->check == 0)
	{
		return (STORE)0;
	}
	else
		return temp->store;
}

#endif
