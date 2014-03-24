
#include <stdio.h>
#include "matrix.h"


int pow(int n, int r)
{
	if( r <= 0 )
	{
		return 1;
	}
	return n * pow(n, r - 1);
}

int main()
{
	Matrix<int> m = Matrix<int>(9,9);
	std::vector<std::vector<int> >& inter = m.getInternal();

	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			inter[i][j] = pow(i + 1, j);
		}
	}

	m = m.genRowEchelonForm();
	inter = m.getInternal();

	for(int i = 0; i < 9; ++i)
	{
		printf("[ ");
		for(int j= 0; j < 9; ++j)
		{
			printf("%d ", inter[i][j]);
		}
		printf("]\n");
	}

	return 0;
}
