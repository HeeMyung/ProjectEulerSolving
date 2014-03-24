#include<stdio.h>
#include"bigint.h"

int main()
{
	BIGINTptr temp = numSet(bigInt(30),20122223);
	BIGINTptr temp2 = numSet(bigInt(30),-3999709);
	BIGINTptr temp3 = bigInt(30);

	printNumln(temp);
	printNumln(temp2);
	printNumln(numProduct(temp,temp2,temp3));

	BIGARRAYptr temparray = bigArray(0,bigInt(20),10,30);
	setArrayNum(temparray,temp,1235,temp2);
	printf("%d\n",getArraySmallNum(temparray,temp));
	printNumln(getArrayBigNum(temparray,temp));

	releaseArray(temparray);
}
