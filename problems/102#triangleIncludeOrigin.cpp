#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct point
{
	point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	point(){}
	int x;
	int y;
};

bool checkDivide(point a, point b, point c)
{
	double theta = atan2((double)a.y, (double)a.x);
	double msintheta = -sin(theta);
	double costheta = cos(theta);
	return (msintheta * b.x + costheta * b.y) * (msintheta * c.x + costheta * c.y) < 0;
}

bool checkTriangle(point a, point b, point c)
{
	return checkDivide(a, b, c) && checkDivide(b, a, c) && checkDivide(c, a, b);
}

int main()
{
	FILE* inp = fopen("triangles.txt", "r");
	char buf[2048] = {0};
	int count = 0;
	while(fgets(buf, sizeof(buf), inp) != NULL)
	{
		char* tok =	strtok(buf, ",");
		int i;
		point a, b, c;
		a.x = atoi(tok);
		tok = strtok(NULL, ",");
		a.y = atoi(tok);
		tok = strtok(NULL, ",");
		b.x = atoi(tok);
		tok = strtok(NULL, ",");
		b.y = atoi(tok);
		tok = strtok(NULL, ",");
		c.x = atoi(tok);
		tok = strtok(NULL, ",");
		c.y = atoi(tok);
		printf("(%d, %d) (%d, %d) (%d, %d)\n", a.x, a.y, b.x, b.y, c.x, c.y);
		count += checkTriangle(a,b,c) ? 1 : 0;
	}
	if( checkTriangle(point(-340, 495), point(-153, -910), point(835, -947)) )
		printf("exact!\n");
	else
		printf("fuck!\n");
	if( !checkTriangle(point(-175, 41), point(-421, -714), point(574, -645)) )
		printf("exact!\n");
	else
		printf("fuck!\n");
	printf("A : %d\n", count);
	return 0;
}
