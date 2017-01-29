#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include "library/special_sumset/special_sumset.h"

int main()
{
	FILE* inp = fopen("sets.txt", "r");
	char buffer[1024];
	int sum = 0;
	while(fgets(buffer, sizeof(buffer), inp) != NULL)
	{
		SpecialSumSet t;
		std::set<int> inputset;
		const char* tokken;
		tokken = strtok(buffer, ",");
		while(tokken != NULL)
		{
			int elem = atoi(tokken);
			printf("%d ", elem);
			inputset.insert(elem);
			tokken = strtok(NULL, ",");
		}
		std::set<int>::reverse_iterator setIter = inputset.rbegin();
		int prevValue = 0;
		while(setIter != inputset.rend())
		{
			if( prevValue > 0 )
				t += prevValue - *setIter;
			prevValue = *setIter;
			++setIter;
		}
		t += prevValue;
		t.PrintInternal();
		if( t.CompareCheck() && t.UnicSumCheck() )
			sum += t.elemSum;
		printf("\n");
	}
	printf("sum : %d\n", sum);
}
