#ifndef __LIST_H_
#define __LIST_H_

#include<stdlib.h>
#include"error.h"

#include"struct.h"

typedef struct LISTELEMENT
{
	ELEMENT element;
	struct LISTELEMENT* next;
	struct LISTELEMENT* before;
}LISTELEMENT,*LISTELEMENTptr;
typedef struct LIST
{
	LISTELEMENTptr head;	// 리스트의 헤드
	LISTELEMENTptr end;		// 리스트의 끝
	int listsize;
}LIST,*LISTptr;	// 리스트 스트럭쳐 외부에서는 이 리스트 스트럭쳐와 ELEMENT 스트럭쳐만 알면 된다.

LISTptr newList()	// 뉴 리스트 생성
{
	 LISTptr ret = (LISTptr)calloc(1,sizeof(LIST));
	 ret->end = ret->head = 0;
	 ret->listsize =0;
	 return ret;
}		// 처음에는 아무 인자도 들어가 있지 않은 리스트릴 리턴함.

LISTELEMENTptr newListElement(ELEMENT ele)
{
	LISTELEMENTptr ret = (LISTELEMENTptr)calloc(1,sizeof(LISTELEMENT));
	ret->next = 0;
	ret->before = 0;
	ret->element = ele;
	return ret;
}

void listPushEnd(LISTptr list, ELEMENT ele)	// 리스트의 끝에 element를 추가한다.
{
	if( list->listsize == 0 )
	{
		//	가장 처음의 케이스이다.
		list->head = newListElement(ele);
		list->end = list->head;
	}
	else
	{
		list->end->next = newListElement(ele);
		list->end->next->before = list->end;
		list->end = list->end->next;
	}
	list->listsize++;
}
void listDeleteEnd(LISTptr list)
{
	if( list->listsize == 0 )
	{
		// 에러케이스 처리하기 귀찮다....
		error("List: null exception(empty list)");
	}
	else if(list->listsize == 1)
	{
		free(list->end);
		list->head = 0;
		list->end = 0;
	}
	else
	{
		list->end = list->end->before;
		free(list->end->next);
		list->end->next = 0;
	}
	list->listsize--;
}
void listDeleteHead(LISTptr list)
{
	if(list->listsize == 0)
	{
		error("List: null exception(empty list)");
	}
	else if(list->listsize == 1)
	{
		free(list->head);
		list->head = 0;
		list->end = 0;
	}
	else
	{
		LISTELEMENTptr temp = list->head;
		list->head = temp->next;
		temp->next->before = 0;
		free(temp);
	}
	list->listsize--;
}

void listClear(LISTptr list)
{
	LISTELEMENTptr temp;
	while(list->head != 0)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	list->head = list->end = 0;
	list->listsize = 0;
}
LISTELEMENTptr getListElement(LISTptr list, int index)
{
	int k;
	LISTELEMENTptr ret = list->head;
	for(k =0; k < index; k++)
	{
		if( ret == 0 )
		{
			error("List: Invalid Index");
		}
		ret = ret->next;
	}
	return ret;
}

void listPushIndex(LISTptr list, int index, ELEMENT ele)
{
	LISTELEMENTptr temp = getListElement(list,index);
	LISTELEMENTptr put = newListElement(ele);
	if(index == 0)
	{
		put->next = temp;
		temp->before = put;
	}
	else
	{
		put->before = temp->before;
		temp->before->next = put;
		temp->before = put;
		put->next = temp;
	}
	list->listsize++;
}

void listDeleteIndex(LISTptr list, int index)
{
	LISTELEMENTptr temp = getListElement(list,index);
	temp->before->next = temp->next;
	if(index != list->listsize)
		temp->next->before = temp->before;
	free(temp);
	list->listsize--;
}
ELEMENT listGetFront(LISTptr list)
{
	if(list->listsize == 0)
	{
		error("List: Zero List");
	}
	return list->head->element;
}
ELEMENT listGetBack(LISTptr list)
{
	if(list->listsize == 0)
		error("List: Zero List");
	return list->end->element;
}
ELEMENT listGetIndex(LISTptr list,int index)
{
	LISTELEMENTptr temp = getListElement(list,index);
	return temp->element;
}


int _itertemp__;
LISTELEMENTptr _itertemp_;

#define listIter(list,eleptr)	for(_itertemp__ = 0,_itertemp_ = list->head,eleptr = &_itertemp_->element ; _itertemp__ < list->listsize; _itertemp__++,_itertemp_ = _itertemp_->next,eleptr = &_itertemp_->element)

#endif
