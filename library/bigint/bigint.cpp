#include "bigint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define checkpoint(x)	{printf("check %s %s %d\n", x,  __FILE__, __LINE__);}
#define big(a,b)	(a > b ? a : b)

BigInt::BigInt()
{
	m_internal.resize(0);
}

BigInt::~BigInt()
{
}

BigInt::BigInt(const int& i)
{
	if( i < 0 )
	{
		*this = -i;
	}
	else
	{
		*this = i;
	}
}

BigInt BigInt::operator=(const int& i)
{
	char temp[100] = {0};
	int t = i;
	int count = 0;
	if( i == 0 )
	{
		m_internal.resize(1);
		m_internal[0] = 0;
		return *this;
	}
	while(t > 0)
	{
		temp[count++] = t%10;
		t /= 10;
	}
	m_internal.resize(count);
	memcpy(&m_internal[0], temp, count);
	return *this;
}

BigInt::operator const char*()
{
	m_internal_string = toString();
	return m_internal_string.c_str();
}

const std::vector<char>& BigInt::getInternal() const
{
	return m_internal;
}

std::string BigInt::toString() const
{
	std::string ret;
	ret.resize(m_internal.size() + 1);
	int i, j;
	for(i = m_internal.size()-1, j = 0 ; i >= 0; --i, ++j)
	{
		ret[j] = m_internal[i] + '0';
	}
	ret[j] = '\0';
	return ret;
}

int BigInt::length() const
{
	return m_internal.size();
}

BigInt BigInt::operator+(const BigInt& bi) const
{
	const BigInt *bigger, *smaller;
	if( m_internal.size() >= bi.m_internal.size() )
	{
		bigger = this;
		smaller = &bi;
	}
	else
	{
		bigger = &bi;
		smaller = this;
	}

	int bigsize = bigger->m_internal.size();
	int smallsize = smaller->m_internal.size();

	char* temp = new char[bigsize+1];
	memset(temp, 0, bigsize+1);
	
	int i;
	int carry = 0;
	for(i = 0; i < smallsize; ++i)
	{
		int intercalc = smaller->m_internal[i] + bigger->m_internal[i] + carry;
		if( intercalc >= 10 )
		{
			carry = 1;
			intercalc -= 10;
		}
		else
		{
			carry = 0;
		}
		temp[i] = intercalc;
	}
	for(; i < bigsize; ++i)
	{
		int intercalc = bigger->m_internal[i] + carry;
		if( intercalc >= 10 )
		{
			carry = 1;
			intercalc -= 10;
		}
		else
		{
			carry = 0;
		}
		temp[i] = intercalc;
	}
	if( carry == 1 )
	{
		temp[bigsize++] = 1;
	}
	
	BigInt ret;
	ret.m_internal.resize(bigsize);
	memcpy(&ret.m_internal[0], temp, bigsize);

	delete[] temp;

	return ret;
}

void BigInt::operator++(int)
{
	m_internal[0]++;
	int i;
	for(i = 0; i < m_internal.size()-1; ++i)
	{
		if( m_internal[i] < 10 )
		{
			return;
		}
		m_internal[i] = 0;
		m_internal[i+1]++;
	}
	if(	m_internal[i] > 9 )
	{
		// 크기 늘어남.. ㄷㄷ; ㅠ
		std::vector<char> newInter;
		newInter.resize(m_internal.size()+1);
		memcpy(&newInter[0], &m_internal[0], m_internal.size());
		newInter[i] = 0;
		newInter[i+1] = 1;
		m_internal = newInter;
	}
}

BigInt BigInt::operator+(const int& i) const
{
	return operator+(BigInt(i));
}

BigInt BigInt::puresubt(const BigInt& bi) const
{
	// if the operand bigger than this.. return zero
	if ( bi > *this )
	{
		return BigInt(0);
	}

	int bigsize = length();
	int smallsize = bi.length();
	int i;
	const std::vector<char> &me = getInternal(), &yours = bi.getInternal();
	int carry = false;
	char *temp = new char[bigsize];
	for(i = 0; i < smallsize; ++i)
	{
		temp[i] = me[i] - yours[i] - carry;
		if( temp[i] < 0 )
		{
			carry = 1;
			temp[i] += 10;
		}
		else
		{
			carry = 0;
		}
	}
	for(; i < bigsize; ++i)
	{
		temp[i] = me[i] - carry;
		if( temp[i] < 0 )
		{
			carry = 1;
			temp[i] += 10;
		}
		else
		{
			i++;
			break;
		}
	}
	// 남은 리스트를 카피한다.
	memcpy(&temp[i], &me[i], bigsize - i);

	BigInt ret = resolve(temp, bigsize);	
	delete[] temp;
	return ret;
}

BigInt BigInt::operator-(const BigInt& bi) const
{
	return puresubt(bi);
}

int BigInt::isBigger(const BigInt& a, const BigInt& b) const
{
	int mysize = a.length();
	int yoursize = b.length();
	if( mysize > yoursize )
	{
		return -1;
	}
	else if( mysize < yoursize )
	{
		return 1;
	}

	const std::vector<char> &my = a.getInternal(), &yours = b.getInternal();

	// after this line.. the two number has same length;;;
	int i;
	for(; mysize > 0; --mysize)
	{
		if( my[mysize-1] == yours[mysize-1] )
		{
			continue;
		}
		else if( my[mysize-1] > yours[mysize-1] )
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	
	// at this time.. two number is same;;
	return 0;
}

bool BigInt::operator>(const BigInt& bi) const
{
	return isBigger(*this, bi) < 0;
}

bool BigInt::operator<(const BigInt& bi) const
{
	return isBigger(bi , (*this)) < 0;
}
bool BigInt::operator==(const BigInt& bi) const
{
	return isBigger(*this, bi) == 0;
}

bool BigInt::operator>=(const BigInt& bi) const
{
	return isBigger(*this, bi) <= 0;
}

bool BigInt::operator<=(const BigInt& bi) const
{
	return isBigger(*this, bi) >= 0;
}

BigInt BigInt::operator*(const int& i) const
{
	BigInt prod = BigInt(i);
	return prod * (*this);
}

BigInt BigInt::operator*(const BigInt& bi) const
{
	int mySize = length();
	int yourSize = bi.length();
	int size = mySize + yourSize;
	int* temp = new int[size];
	memset(temp, 0, size * sizeof(int));
	const std::vector<char> &my = getInternal(), &your = bi.getInternal();

	int i,j;
	for(i = 0; i < mySize; ++i)
	{
		for(j = 0; j < yourSize; ++j)
		{
			temp[i+j] += my[i] * your[j];
		}
	}
	int intercalc = 0;
	for(i = 0; i < size-1; i++)
	{
		intercalc += temp[i];
		temp[i] = intercalc%10;
		intercalc /= 10;
	}
	temp[size-1] = intercalc;
	BigInt ret = resolve(temp, size);
	delete[] temp;
	return ret;
}

BigInt BigInt::operator/(const BigInt& bi) const
{
	BigInt cp = bi, cp2 = *this;
	//printf("%s/%s\n", (const char*)cp2, (const char*)cp);
	if( *this < bi )
	{
		return BigInt(0);
	}
	BigInt preset[10];
	int i;
	for(i = 0; i < 10; ++i)
	{
		preset[i] = bi * i;
	}

	int divideeSize = length();
	int dividerSize = bi.length();
	char* temp = NULL;
	try
	{
		temp = new char[divideeSize];
	}
	catch(std::bad_alloc e)
	{
		printf("e.what() : %s\n", e.what());
		return BigInt(0);
	}
	memset(temp, 0, divideeSize);
	BigInt cpy;
	cpy = *this;
	for(i = divideeSize - dividerSize; i >= 0; --i)
	{
		//printf("current cpy : %s\n", (const char*)cpy);
		if( cpy == BigInt(0) )	// 나누어 떨어져버림
		{
			break;
		}
		if( cpy.length() - i < 1 )
		{
			continue;
		}
		BigInt cutOff = resolve(&cpy.m_internal[i], cpy.length() - i);
		//printf("cutOff : %s\n", (const char*)cutOff);
		int j;
		for(j = 9; j > 0; --j)
		{
			if( cutOff >= preset[j] )
			{
				break;
			}
		}
		temp[i] = j;
		cutOff = cutOff - preset[j];
		//printf("remain : %s\n", (const char*)cutOff);
		memcpy(&cpy.m_internal[i], &cutOff.m_internal[0], cutOff.length());
		cpy = resolve(&cpy.m_internal[0], i + cutOff.length());
		//printf("next cpy : %s\n", (const char*) cpy);
	}
	BigInt ret = resolve(temp, divideeSize);
	delete[] temp;
	return ret;
}

BigInt BigInt::operator%(const BigInt& bi) const
{
	if( *this < bi )
	{
		return *this;
	}
	BigInt preset[10];
	int i;
	for(i = 0; i < 10; ++i)
	{
		preset[i] = bi * i;
	}

	int divideeSize = length();
	int dividerSize = bi.length();
	char* temp = new char[divideeSize];
	memset(temp, 0, divideeSize);
	BigInt cpy;
	cpy = *this;
	for(i = divideeSize - dividerSize; i >= 0; --i)
	{
		if( cpy == BigInt(0) )	// 나누어 떨어져버림
		{
			return BigInt(0);
		}
		BigInt cutOff = resolve(&cpy.m_internal[i], cpy.length() - i);
		int j;
		for(j = 9; j > 0; --j)
		{
			if( cutOff >= preset[j] )
			{
				break;
			}
		}
		temp[i] = j;
		cutOff = cutOff - preset[j];
		memcpy(&cpy.m_internal[i], &cutOff.m_internal[0], cutOff.length());
		cpy = resolve(&cpy.m_internal[0], i + cutOff.length());
	}
	delete[] temp;
	return cpy;
}

void BigInt::fillWith(int size, char value)
{
	if( size > m_internal.size() )
	{
		return;
	}
	int i;
	memset(&m_internal[0], value, size);
}

BigInt BigInt::cut(int start, int end)
{
	int len = length();
	if( end >= len )
		end = len-1;
	start = len - start - 1;
	end = len - end - 1; 
	return resolve(&m_internal[end], start - end + 1);
}
BigInt BigInt::rcut(int start, int end)
{
	int len = length();
	if( end >= len )
		end = len-1;
	return resolve(&m_internal[start], end - start + 1);
}
