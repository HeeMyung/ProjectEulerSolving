#include "permutation.h"
#include "combination.h"

int main()
{
	/*
	HeeM::Permutation<int> p;
	for(int i = 1; i < 10; ++i)
	{
		p.AddElement(i);
	}

	p.Start();
	do
	{
		std::vector<int> outVector;
		p.GetCurrentSelection(outVector);
		for(std::vector<int>::iterator iter = outVector.begin(); iter != outVector.end(); ++iter)
		{
			printf("%d ", *iter);
		}
		printf("\n");
	}while(p.ProcessNextState());
	*/

	HeeM::Combination<int> c;
	for(int i = 1; i <= 10; ++i)
	{
		c.AddElement(i);
	}
	c.Start(1);

	do
	{
		std::vector<int> outVector;
		c.GetSelection(outVector);
		for(std::vector<int>::iterator iter = outVector.begin(); iter != outVector.end(); ++iter)
		{
			printf("%d ", *iter);
		}
		printf("\n");
	}while(c.ProcessNextSelection());
}
