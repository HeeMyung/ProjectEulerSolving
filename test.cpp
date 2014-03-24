#include<stdio.h>

#define HELLO 3/2

int main()
{
	int x = 1;
	int y = 1;

	char test[HELLO];
	printf("%d\n", HELLO);

	int target = 246;

	for(int i = 2; i < target; ++i)
	{
		if( target%i == 0 )
		{
			printf("i : %d\n", i);
		}
	}

	return 0;
}
