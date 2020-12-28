#ifndef __COMBINATION_H_
#define __COMBINATION_H_

#include <vector>

namespace HeeM
{
	template<class C>
	class Combination
	{
	public:
		void Reset();
		void AddElement(C elem);
		void Start(size_t selectCount);
		void GetSelection(std::vector<C>& out_selection);
		bool ProcessNextSelection();
	private:
		std::vector<C> m_elements;
		std::vector<int> m_fingers;
		size_t m_limitPos;
		size_t m_selectCount;
	};

	template<class C>
	void Combination<C>::Reset()
	{
		m_elements.clear();
		m_fingers.clear();
		m_limitPos = 0;
	}

	template<class C>
	void Combination<C>::AddElement(C elem)
	{
		m_elements.push_back(elem);
	}

	template<class C>
	void Combination<C>::Start(size_t selectCount)
	{
		if( selectCount > m_elements.size() )
			selectCount = m_elements.size();

		m_fingers.resize(selectCount);
		for(size_t i = 0; i < selectCount; ++i)
		{
			m_fingers[i] = (int)i;
		}
		m_selectCount = selectCount;
		m_limitPos = m_elements.size();
	}

	template<class C>
	void Combination<C>::GetSelection(std::vector<C>& out_selection)
	{
		out_selection.resize(m_selectCount);
		for(int i = 0; i < m_selectCount; ++i)
		{
			out_selection[i] = m_elements[m_fingers[i]];
		}
	}

	template<class C>
	bool Combination<C>::ProcessNextSelection()
	{
		int endPoint = m_limitPos-1;
		int foundPos = m_selectCount-1;
		for(; foundPos >= 0; --foundPos, --endPoint)
		{
			if( endPoint != m_fingers[foundPos] )
			{
				//printf("endPoint:%d, m_fingers[%d]:%d\n", endPoint, foundPos, m_fingers[foundPos]);
				break;
			}
		}
		if( foundPos < 0 )
		{
			return false;
		}
		m_fingers[foundPos]++; 
		for(int i = foundPos+1; i < m_selectCount; ++i)
		{
			m_fingers[i] = m_fingers[i-1]+1;
		}
		return true;
	}
}

#endif
