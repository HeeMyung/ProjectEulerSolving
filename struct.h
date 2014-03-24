#ifndef __STRUCT_H_
#define __STRUCT_H_

typedef union ELEMENT
{
	int n;
	char c;
	short s;
	void* ptr;
	char* cptr;
}ELEMENT,*ELEMENTptr;

#endif
