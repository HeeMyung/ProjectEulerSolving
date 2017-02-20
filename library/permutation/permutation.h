#ifndef __PERMUTATION_H_
#define __PERMUTATION_H_

#include <vector>

namespace HeeM
{
	template<class C>
		class Permutation
		{
			public:
				void Reset();

				void AddElement(C element);
				void Start();
				void GetCurrentSelection(std::vector<C>& out_selection);
				bool ProcessNextState();	// if return is false.. there's no permutations left.
			private:
				void ProcessNextStateSub(int curPos);
				bool CheckNoMore(int pos);
				std::vector<C> m_elements;
				std::vector<int> m_currentState;
				int m_limitPos;
		};

	template<class C>
		void Permutation<C>::Reset()
		{
			m_elements.clear();
			m_currentState.clear();
		}

	template<class C>
		void Permutation<C>::AddElement(C element)
		{
			m_elements.push_back(element);
		}

	template<class C>
		void Permutation<C>::Start()
		{
			m_currentState.resize(m_elements.size());
			m_limitPos = m_elements.size();
			for(size_t i = 0; i < m_limitPos; ++i)
			{
				m_currentState[i] = i;
			}
		}

	template<class C>
		void Permutation<C>::GetCurrentSelection(std::vector<C>& out_selection)
		{
			out_selection.clear();
			for(std::vector<int>::iterator iter = m_currentState.begin(); iter != m_currentState.end(); ++iter)
			{
				out_selection.push_back(m_elements[*iter]);
			}
		}

	template<class C>
		bool Permutation<C>::ProcessNextState()
		{
			if( CheckNoMore(0) )
				return false;
			ProcessNextStateSub(0);
			return true;
		}

	template<class C>
		void Permutation<C>::ProcessNextStateSub(int curPos)
		{
			//printf("ProcessNextStateSub\n");
			if( !CheckNoMore(curPos+1) )
			{
				ProcessNextStateSub(curPos+1);
				return;
			}
			int curIndex = m_currentState[curPos];
			//printf("curIndex:%d\n", curIndex);

			std::vector<int> rerangeVec;
			rerangeVec.resize(m_limitPos);
			for(int i = 0; i < m_limitPos; ++i)
			{
				rerangeVec[i] = 0;
			}
			for(int i = curPos; i < m_limitPos; ++i)
			{
				rerangeVec[m_currentState[i]]++;
			}
			int found = curIndex + 1;
			for(; found < m_limitPos; ++found)
			{
				if( rerangeVec[found] > 0 )
					break;
			}
			m_currentState[curPos++] = found;
			rerangeVec[found]--;

			for(int i = 0; i < m_limitPos; ++i)
			{
				//printf("rerangeVec[%d]:%d\n", i, rerangeVec[i]);
				while(rerangeVec[i]>0)
				{
					m_currentState[curPos++] = i;
					rerangeVec[i]--;
				}
			}
			/*
			   printf("next state position infos : ");
			   for(int i = 0; i < m_limitPos; ++i)
			   {
			   printf("%d ", m_currentState[i]);
			   }
			   printf("\n");
			 */
		}

	template<class C>
		bool Permutation<C>::CheckNoMore(int pos)
		{
			//printf("pos:%d, m_limitPos:%d\n", pos, m_limitPos);
			if( pos >= m_limitPos - 1)
				return true;
			else if( m_currentState[pos] < m_currentState[pos+1] )
				return false;
			else
				return CheckNoMore(pos+1);
		}
}
#endif
