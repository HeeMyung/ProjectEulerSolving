#include <stdio.h>
#include "matrix.h"

std::vector<long long> g_answerList;

void PrintMatrix(Matrix<long long> m)
{
	int i;
	for(i = 0; i < m.getRowCount(); ++i)
	{
		printf("[ ");
		for(int j = 0; j < m.getColumnCount(); j++)
		{
			long long t = m[i][j];
			printf("%10lld ", t);
		}
		printf("]\n");
	}
}

long long ipower(long long n, long long r)
{
	if( r <= 0 )
	{
		return 1;
	}
	return n * ipower(n, r - 1);
}

Matrix<long long> GenBadOpMatrix(long long level)
{
	Matrix<long long> ret(level, level + 1);

	for(int i = 0; i < level; ++i)
	{
		for(int j = 0; j < level; ++j)
		{
			ret[i][j] = ipower((long long)i + 1, (long long)j);
		}
		ret[i][level] = g_answerList[i+1];
	}
	//PrintMatrix(ret);
	ret = ret.genRowEchelonForm();
	return ret;
}

std::vector<long long> GetAnswerFromMatrix(Matrix<long long> refed_bop)
{
	std::vector<long long> ret, line;
	ret.resize(refed_bop.getRowCount());

	int i;

	for(i = refed_bop.getRowCount() - 1; i >= 0 ; --i)
	{
		line = refed_bop[i];
		for(int j = i + 1; j < refed_bop.getRowCount() ; ++j)
		{
			line[refed_bop.getRowCount()] -= ret[j] * line[j];
		}
		ret[i] = line[refed_bop.getRowCount()]/line[i];
	}
	return ret;
}

long long GetBadOpVal(std::vector<long long> a)
{
	long long ret = 0;
	int i;
	for(i = 0; i < a.size(); ++i)
	{
		ret += a[i] * ipower(a.size()+1, i);
	}
	return ret;
}

int main()
{
	long long i;
	g_answerList.resize(12);
	for(i = 1; i < 11; ++i)
	{
		g_answerList[i] = (ipower(i, 11) + 1) / (i + 1);
	}
	Matrix<long long> bopMat;
	long long rret = 0;
	for(i = 1; i < 11; ++i)
	{
		bopMat = GenBadOpMatrix(i);
		//PrintMatrix(bopMat);
		std::vector<long long> answer = GetAnswerFromMatrix(bopMat);
		long long danswer = GetBadOpVal(answer);
		rret += danswer;
	}
	printf("A : %lld\n", rret);
}
