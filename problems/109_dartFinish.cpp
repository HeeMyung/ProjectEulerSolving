#include <stdio.h>
#include <set>
#include <map>
#include <vector>

struct SCORE
{
	SCORE()
	{
	}
	SCORE(int _prod, int _score) : prod(_prod), score(_score)
	{
	}
	int prod;
	int score;

	void print(bool newline = true) const
	{
		char prodv;
		switch(prod)
		{
			case 1:
				prodv = 'S';
				break;
			case 2:
				prodv = 'D';
				break;
			case 3:
				prodv = 'T';
				break;
			default:
				prodv = 'N';
				break;
		}
		printf("%c%d", prodv, score);
		if( newline )
			putchar('\n');
	}

	bool operator<(const SCORE& s) const
	{
		return prod < s.prod ? true : prod > s.prod ? false : score < s.score ? true : false;
	}
};



int main()
{
	std::vector<SCORE> scorePreset;
	for(int i = 1; i <= 20; ++i)
	{
		for(int j = 1; j <= 3; ++j)
		{
			SCORE s(j, i);
			scorePreset.push_back(s);
		}
	}
	for(int i = 1; i <= 2; ++i)
	{
		SCORE bull_eye;
		bull_eye.score = 25;
		bull_eye.prod = i;
		scorePreset.push_back(bull_eye);
	}

	std::vector<SCORE> doubleScorePreset;
	for(int i = 1; i <= 20; ++i)
	{
		SCORE s(2, i);
		doubleScorePreset.push_back(s);
	}
	doubleScorePreset.push_back(SCORE(2,25));

	printf("점수 프리셋 다 만듬\n");

	std::set< std::vector<SCORE> > passibleSet;
	passibleSet.insert(std::vector<SCORE>());
	for(std::vector<SCORE>::iterator iter = scorePreset.begin(); iter != scorePreset.end(); ++iter)
	{
		std::vector<SCORE> addset;
		addset.push_back(*iter);
		passibleSet.insert(addset);
		for(std::vector<SCORE>::iterator iter2 = iter; iter2 != scorePreset.end(); ++iter2)
		{
			std::vector<SCORE> addset2 = addset;
			addset2.push_back(*iter2);
			passibleSet.insert(addset2);
		}
	}

	printf("다 만듬\n");

	int count = 0;
	for(std::vector<SCORE>::iterator iter = doubleScorePreset.begin(); iter != doubleScorePreset.end(); ++iter)
	{
		const SCORE& s = *iter;
		for(std::set< std::vector<SCORE> >::iterator setIter = passibleSet.begin(); setIter != passibleSet.end(); ++setIter)
		{
			int total = s.prod * s.score;
			std::vector<SCORE> curScore = *setIter;
			for(std::vector<SCORE>::iterator innerIter = curScore.begin(); innerIter != curScore.end(); ++innerIter)
			{
				const SCORE& ss = *innerIter;
				total += ss.prod * ss.score;
			}
			if( total < 100 )
			{
				count++;
			}
		}
	}
	printf("count : %d\n", count);
}
