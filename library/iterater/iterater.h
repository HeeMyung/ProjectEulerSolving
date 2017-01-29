#pragma once

#include <queue>
#include <set>
#include <vector>
#include "../common/common.h"

template<typename T, std::vector<T>(*Generater)(const T&), typename Pred = std::less<T>>
class PriorityIterater
{
public:
	PriorityIterater(T start, bool noDuplicate = true) : m_allowDup(!noDuplicate)
	{
		m_queue.push(start);
		m_checkedSet.insert(start);
	}

	bool GetNext(T& out)
	{
		if( m_queue.empty() )
		{
			return false;
		}
		T ret = m_queue.top();
		m_queue.pop();
		for(auto newElem : Generater(ret))
		{
			if( !m_allowDup && m_checkedSet.find(newElem) != m_checkedSet.end() )
				continue;
			m_checkedSet.insert(newElem);
			m_queue.push(newElem);
		}
		out = ret;
		return true;
	}
	bool m_allowDup;
	std::set<T, Pred> m_checkedSet;
	std::priority_queue<T, std::vector<T>, Pred> m_queue;
};
