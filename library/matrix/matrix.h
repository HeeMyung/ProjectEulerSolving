#ifndef __MATRIX_HEEM_H_
#define __MATRIX_HEEM_H_

#include <vector>

/// Declare ///
template<class T>
class Matrix
{
public:
	Matrix()
	{
		m_rowCount = 0;
		m_columnCount = 0;
	}
	Matrix(int rows, int columns);
	Matrix(const Matrix<T>& m);
	~Matrix(){}

	Matrix<T> operator+(const Matrix<T>& m);

	std::vector< std::vector<T> >& getInternal();
	int getRowCount() const { return m_rowCount; }
	int getColumnCount() const { return m_columnCount; } 
	std::vector<T>& operator[](const int& index);

	void exchangeRow(int r1, int r2); // 내부 구현상 exchangeRow 가 exchangeColumn 보다 빠름
	void exchangeColumn(int c1, int c2);

	void prodCrow(const int row,const T& t);
	void prodCcolumn(const int column, const T& t);

	void addVecToRow(int row, const std::vector<T>& vec);
	void addVecToRow(int row, const std::vector<T>& vec, const T& c);
	void addVecToColumn(int column, const std::vector<T>& vec);
	void addVecToColumn(int column, const std::vector<T>& vec, const T& c);

	Matrix<T> genRowEchelonForm();

private:
	int m_rowCount;
	int m_columnCount;
	std::vector< std::vector<T> > m_internal;
};
template<class T>
inline Matrix<T> operator*(const std::vector<T>& v, Matrix<T> m);

/// Implement ///
template<class T>
Matrix<T>::Matrix(int rows, int columns)
{
	m_internal.resize(rows);
	int i;
	for(i = 0 ; i < rows; ++i)
	{
		m_internal[i].resize(columns);
		for(int j = 0; j < columns; ++j)
		{
			m_internal[i][j] = T();
		}
	}
	m_rowCount = rows;
	m_columnCount = columns;
}
template<class T>
Matrix<T>::Matrix(const Matrix<T>& m) : m_rowCount(m.m_rowCount), m_columnCount(m.m_columnCount)
{
	m_internal.resize(m_rowCount);
	for(int i = 0; i < m_rowCount; ++i)
	{
		m_internal[i].resize(m_columnCount);
		std::vector<T>& vec = m_internal[i];
		std::vector<T> them = m.m_internal[i];
		for(int j = 0; j < m_columnCount; ++j)
		{
			vec[j] = them[j];
		}
	}
}
template<class T>
inline std::vector< std::vector<T> >& Matrix<T>::getInternal()
{
	return m_internal;
}

template<class T>
inline Matrix<T> operator*(const std::vector<T>& v, Matrix<T> m)
{
	return Matrix<T>();
}
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)
{
	if( m_rowCount != m.m_rowCount || m.m_columnCount )
	{
		// 사이즈가 같지 않으면 더할 수 없음.
		return *this;
	}
	Matrix<T> ret(m_rowCount, m_columnCount);
	for(int i = 0; i < m_rowCount; ++i)
	{
		for(int j = 0; j < m_columnCount; ++j)
		{
			ret.m_internal[i][j] = m_internal[i][j] + m.internal[i][j];
		}
	}
	return ret;
}

template<class T>
std::vector<T>& Matrix<T>::operator[](const int& index)
{
	if( index < 0 || index >= m_rowCount )
	{
		printf("[] invalid index: %d\n", index);
		return m_internal[0];
	}
	return m_internal[index];
}
template<class T>
void Matrix<T>::exchangeRow(int r1, int r2)
{
	if( r1 < 0 || r2 < 0 || r1 >= m_rowCount || r2 >= m_rowCount )
	{
		// 입력이 인벨리드
		return;
	}
	T* temp = new T[m_columnCount];
	memcpy(temp, &m_internal[r1][0], sizeof(T) * m_columnCount);
	memcpy(&m_internal[r1][0], &m_internal[r2][0], sizeof(T) * m_columnCount);
	memcpy(&m_internal[r2][0], temp, sizeof(T) * m_columnCount);
	delete[] temp;
}

template<class T>
void Matrix<T>::exchangeColumn(int c1, int c2)
{
	if( c1 < 0 || c2 < 0 || c1 >= m_columnCount || c2 >= m_columnCount )
	{
		// 입력이 인벨리드
		return;
	}
	T* temp = new T[m_rowCount];
	int i;
	for(i = 0; i < m_rowCount; ++i)
	{
		T temp = m_internal[i][c1];
		m_internal[i][c1] = m_internal[i][c2];
		m_internal[i][c2] = temp;
	}
}

template<class T>
void Matrix<T>::prodCrow(const int row, const T& t)
{
	if( row < 0 || row >= m_rowCount )
		// invalid row
		return;
	int i;
	const std::vector<T>& vrow = m_internal[row];
	for(i = 0; i < m_columnCount; ++i)
	{
		vrow[i] *= t;
	}
}
template<class T>
void Matrix<T>::prodCcolumn(const int column, const T& t)
{
	if( column < 0 || column >= m_columnCount)
	{
		// invalid column
		return;
	}
	int i;
	for(i = 0; i < m_rowCount ; ++i)
	{
		m_internal[column] *= t;
	}
}
template<class T>
void Matrix<T>::addVecToRow(int row, const std::vector<T>& vec)
{
	if( m_columnCount != vec.size() || row < 0 || row >= m_rowCount )
	{
		// 조건 불일치.. 
		return;
	}
	const std::vector<T>& vrow = m_internal[row];
	for(int i = 0; i < m_columnCount; ++i)
	{
		vrow[i] += vec[i];
	}
}
template<class T>
void Matrix<T>::addVecToRow(int row, const std::vector<T>& vec, const T& c)
{
	if( m_columnCount != vec.size() || row < 0 || row >= m_rowCount )
	{
		// 조건 불일치.. 
		return;
	}
	int i;
	std::vector<T>& vrow = m_internal[row];
	for(i = 0; i < m_columnCount; ++i)
	{
		vrow[i] += vec[i] * c;
	}
}

template<class T>
void Matrix<T>::addVecToColumn(int column, const std::vector<T>& vec)
{
	if( m_rowCount != vec.size() || column < 0 || column >= m_columnCount )
	{
		// 조건 불일치.. 
		return;
	}
	int i;
	for(i = 0; i < m_columnCount; ++i)
	{
		m_internal[i][column] += vec[i];
	}
}

template<class T>
void Matrix<T>::addVecToColumn(int column, const std::vector<T>& vec, const T& c)
{
	if( m_rowCount != vec.size() || column < 0 || column >= m_columnCount )
	{
		// 조건 불일치.. 
		return;
	}
	int i;
	for(i = 0; i < m_columnCount; ++i)
	{
		m_internal[i][column] += vec[i] * c;
	}
}

template<class T>
Matrix<T> Matrix<T>::genRowEchelonForm()
{
	int i;
	Matrix<T> ret = *this;
	const std::vector< std::vector<T> >& inter = ret.getInternal();
	for(i = 0; i < m_rowCount - 1; ++i)
	{
		for(int j = i + 1; j < m_rowCount; ++j)
		{
			T dest = inter[i][i];
			T comp = inter[j][i];
			ret.addVecToRow(j, inter[i], -comp/dest);
		}
	}
	return ret;
}

#endif
