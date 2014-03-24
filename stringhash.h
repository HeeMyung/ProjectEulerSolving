#ifndef __STRINGHASH_H_
#define __STRINGHASH_H_

#include<stdlib.h>
#include"list.h"
#include"error.h"
#include<string.h>

#define MAXHASH 4000
#define resolve(a) ((a >= 'a') ? (a - 'a') : (a - 'A'))

#define MAXSTRINGSIZE 30

typedef struct HASHENTRY
{
	char value[MAXSTRINGSIZE];
	ELEMENT elt;
}HASHENTRY,*HASHENTRYptr;

typedef struct StringHash
{
	LISTptr hash[MAXHASH];
}STRINGHASH,*STRINGHASHptr;

STRINGHASHptr newStringHash()
{
	STRINGHASHptr ret = (STRINGHASHptr)calloc(1,sizeof(STRINGHASH));
	int k;
	for(k = 0; k < MAXHASH; k++)
	{
		ret->hash[k] = (LISTptr)calloc(1,sizeof(LIST));
	}
	return ret;
}

int hashing(char* str)
{
	int k,prod;
	for(k = 0,prod = 1; str[k] != '\0'; k++)
	{
		prod = (prod * str[k] + k)%4000;
	}
	return prod;
}

int stringIsIn(STRINGHASHptr hash,char* str)
{
	int hashval = hashing(str);
	ELEMENT* hashtemp;

	listIter(hash->hash[hashval],hashtemp)
	{
		if( strcmp(((HASHENTRYptr)((*hashtemp).ptr))->value,str) == 0 )
			return 1;
	}
	return 0;
}

void stringStore(STRINGHASHptr hash,char* str, ELEMENT elt)
{
	int hashval = hashing(str);
	ELEMENT* hashtemp;

	listIter(hash->hash[hashval],hashtemp)
	{
		if( strcmp(((HASHENTRYptr)((*hashtemp).ptr))->value,str) == 0 )
		{
			((HASHENTRYptr)((*hashtemp).ptr))->elt = elt;
			return;
		}
	}
	HASHENTRYptr put = (HASHENTRYptr)calloc(1,sizeof(HASHENTRY));
	strcpy(put->value,str);
	put->elt = elt;
	listPushEnd(hash->hash[hashval],(ELEMENT)(void*)put);
}
ELEMENT stringLoad(STRINGHASHptr hash,char* str)
{
	int hashval = hashing(str);
	ELEMENT* hashtemp;

	listIter(hash->hash[hashval],hashtemp)
	{
		if( strcmp(((HASHENTRYptr)((*hashtemp).ptr))->value,str) == 0 )
		{
			return ((HASHENTRYptr)((*hashtemp).ptr))->elt;
		}
	}
	error("Not Hashed String");
	return (ELEMENT)0;
}

#endif
