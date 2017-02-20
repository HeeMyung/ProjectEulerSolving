#include <stdio.h>
#include "graph.h"

int main()
{
	HeeM::Graph<int> hello;
	hello.AddVertex(1);
	hello.AddVertex(2);
	hello.AddEdge(1,2,3);

	printf("Hello, World! %d\n", hello.GetWeight(1, 2));
}
