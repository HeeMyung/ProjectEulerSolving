#pragma once

#include<stdio.h>

void error(char* str)
{
	printf("error : %s\n",str);
	exit(0);
}
