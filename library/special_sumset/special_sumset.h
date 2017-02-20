struct SubsetSum
{
	int sum;
	int elemCount;

	SubsetSum(int n)
	{
		sum = n;
		elemCount = 1;
	}
	SubsetSum(int _sum, int _elemCount) : sum(_sum), elemCount(_elemCount)
	{
	}
};

struct SpecialSumSet
{
	std::set<int> rSet;
	std::vector<SubsetSum> subsetSumVec;
	int elemSum;
	bool unicSum;
	bool dirty;

	SpecialSumSet()
	{
		rSet.clear();
		subsetSumVec.clear();
		elemSum = 0;
		unicSum = false;
		dirty = true;
	}

	SpecialSumSet operator+(const int a)
	{
		SpecialSumSet ret;
		ret.rSet.insert(a);
		std::set<int>::iterator iter = rSet.begin();
		for(; iter != rSet.end(); ++iter)
		{
			ret.rSet.insert(*iter + a);
		}
		ret.elemSum = elemSum + (rSet.size()+1)*a;
		std::vector<SubsetSum>::iterator subSumIter = subsetSumVec.begin();
		for(; subSumIter != subsetSumVec.end(); ++subSumIter)
		{
			SubsetSum t = *subSumIter;
			t.sum += t.elemCount * a;
			ret.subsetSumVec.push_back(t);
			t.sum += a;
			t.elemCount++;
			ret.subsetSumVec.push_back(t);
		}
		ret.subsetSumVec.push_back(SubsetSum(a));
		ret.dirty = true;
		return ret;
	}

	SpecialSumSet operator=(const SpecialSumSet sss)
	{
		rSet = sss.rSet;
		subsetSumVec = sss.subsetSumVec;
		elemSum = sss.elemSum;
		unicSum = sss.unicSum;
		dirty = sss.dirty;
		return *this;
	}

	SpecialSumSet operator+=(const int a)
	{
		std::set<int> nextRSet;
		std::set<int>::iterator iter = rSet.begin();
		for(; iter != rSet.end(); ++iter)
		{
			nextRSet.insert(*iter + a);
		}
		nextRSet.insert(a);
		rSet = nextRSet;
		elemSum += rSet.size() * a;

		std::vector<SubsetSum> newSubSums;
		std::vector<SubsetSum>::iterator subSumIter = subsetSumVec.begin();
		for(; subSumIter != subsetSumVec.end(); ++subSumIter)
		{
			SubsetSum t = *subSumIter;
			t.sum += t.elemCount * a;
			newSubSums.push_back(t);
			t.sum += a;
			++t.elemCount;
			newSubSums.push_back(t);
		}
		subsetSumVec = newSubSums;

		subsetSumVec.push_back(SubsetSum(a));
		dirty = true;
		return *this;
	}

	bool CompareCheck()
	{
		int size = rSet.size();
		std::vector<int> copy;
		copy.resize(size);
		std::copy(rSet.begin(), rSet.end(), copy.begin());
		for(int i = 1; i <= size/2; ++i)
		{
			int frontSum = 0, backSum = 0;
			for(int j = 0; j < i; ++j)
			{
				frontSum += copy[j];
				backSum += copy[size - j - 1];
			}
			frontSum += copy[i];
			if( frontSum <= backSum )
			{
				return false;
			}
		}
		return true;
	}

	bool UnicSumCheck()
	{
		if( !dirty )
			return unicSum;
		std::set<int> checkSet;
		std::vector<SubsetSum>::iterator iter = subsetSumVec.begin();
		dirty = false;
		for(; iter != subsetSumVec.end(); ++iter)
		{
			if( checkSet.count((*iter).sum) > 0 )
			{
				unicSum = false;
				return false;
			}
			checkSet.insert((*iter).sum);
		}
		unicSum = true;
		return true;
	}

	void PrintInternal()
	{
		printf("SpecialSumSet : %s, Elements : { ", CompareCheck() && UnicSumCheck() ? "True" : "False");
		std::set<int>::iterator iter = rSet.begin();
		for(; iter != rSet.end(); ++iter)
		{
			printf("%d ", *iter);
		}
		printf("}, elemSum : %d\n", elemSum);
		std::vector<SubsetSum>::iterator subSumIter = subsetSumVec.begin();
		printf("subsetSums : { ");
		for(; subSumIter != subsetSumVec.end(); ++subSumIter)
		{
			printf("%d ", (*subSumIter).sum);
		}
		printf("}\n");
	}
};
