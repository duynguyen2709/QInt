#include "QInt.h"
#include "Utilities.h"

QInt QInt::QINT_MAX(10, "0");
QInt QInt::QINT_MIN(10, "0");

QInt QInt::SplitNumber(string binary)
{
	QInt result;

	int digit0 = MAX_BIT_LENGTH - binary.length();

	for ( int i = 0; i < digit0; i++ )
	{
		binary = "0" + binary;
	}

	string str = "";
	int k = 0;
	for ( int i = 1; i <= MAX_BIT_LENGTH; i++ )
	{
		str += binary[i - 1];
		if ( i % 32 == 0 )
		{
			result.data[k++] = bitset<32>(str).to_ulong();
			str.clear();
		}
	}
	return result;
}

void QInt::InitializeLimits()
{
	string max = "0";
	string min = "1";

	for ( int i = 0; i < 127; i++ )
	{
		max += "1";
		min += "1";
	}

	QINT_MAX = *( new QInt(2, max) );
	QINT_MIN = *( new QInt(2, min) );

}

QInt::QInt()
{
	for ( size_t i = 0; i < 4; i++ )
	{
		data[i] = 0;
	}

}

QInt::QInt(int base, string num)
{
	OverflowException ex;
	if ( num == "" )
		( *this ) = *( new QInt(10, "0") );

	Utilities A;

	for ( size_t i = 0; i < 4; i++ )
	{
		data[i] = 0;
	}
	if ( base == 10 )
	{
		if ( num[0] != '-' )
		{
			*this = SplitNumber(A.DecToBin(num));

			if ( (int) ( ( data[0] >> 31 ) & 1 ) == 1 )
				throw ex;
		}
		else
		{
			*this = SplitNumber(A.DecToBin(num.substr(1)));
			data[0] = data[0] | 1 << 31;
		}
	}
	else if ( base == 2 )
	{
		if ( num.length() <= MAX_BIT_LENGTH )
			*this = A.BinToDec(A.StringToBinary(num));

		else
			throw ex;
	}
	else if ( base == 16 )
	{
		*this = A.HexToDec((char *) num.c_str());
	}

}

QInt::~QInt()
{};

bool QInt::isNegative()
{
	return ( ( data[0] >> 31 ) & 1 ) == 1 ? true : false;
}

QInt QInt::Abs()
{
	QInt result = *this;
	result.data[0] &= ~( 1UL << 31 );
	return result;
}

bool QInt::operator==(const QInt & A)
{
	for ( int i = 3; i >= 0; i-- )
	{
		if ( A.data[i] != data[i] )
			return false;
	}
	return true;
}

bool QInt::operator>(const QInt & A)
{
	if ( *this == A )
		return false;

	bool is_A_Negative = ( (QInt) A ).isNegative();

	bool is_This_Negative = isNegative();

	// (*this < 0 && A > 0)
	if ( is_This_Negative && !is_A_Negative )
		return false;

	// (*this > 0 && A < 0)
	else if ( !is_This_Negative && is_A_Negative )
		return true;

	// (*this > 0 && A > 0)
	else if ( !is_A_Negative && !is_This_Negative )
	{
		for ( int i = 0; i < 4; i++ )
		{
			if ( data[i] > A.data[i] )
				return true;
			else if ( data[i] < A.data[i] )
				return false;
		}
	}
	else // (*this < 0 && A < 0)
	{
		for ( int i = 0; i < 4; i++ )
		{
			if ( data[i] < A.data[i] )
				return true;
			else if ( data[i] > A.data[i] )
				return false;
		}
	}

	return false;
}

QInt QInt::operator+(const QInt & A)
{
	QInt result;

	int remainder = 0;
	for ( int i = 0; i < MAX_BIT_LENGTH; i++ )
	{
		int block = 3 - i / 32;
		int bitPos = i % 32;
		int a1, b1;
		a1 = data[block] >> bitPos & 1;
		b1 = A.data[block] >> bitPos & 1;

		if ( a1 == 0 && b1 == 0 && ( remainder == 1 ) )
		{
			remainder = 0;
			result.data[block] = 1 << bitPos | result.data[block];
			continue;
		}

		if ( a1 == 0 && b1 == 0 && ( remainder == 1 ) )
		{
			remainder = 1;
			result.data[block] = 1 << bitPos | result.data[block];
			continue;
		}
		if ( a1 == 1 && b1 == 1 && ( remainder == 0 ) )
		{
			remainder = 1;
			result.data[block] = 0 << bitPos | result.data[block];
			continue;
		}
		if ( a1 == 1 && b1 == 1 && ( remainder == 1 ) )
		{
			remainder = 1;
			result.data[block] = 1 << bitPos | result.data[block];
			continue;
		}
		if ( ( ( a1 == 0 && b1 == 1 ) || ( a1 == 1 && b1 == 0 ) ) && remainder == 1 )
		{
			remainder = 1;
			result.data[block] = 0 << bitPos | result.data[block];
			continue;
		}
		if ( ( ( a1 == 0 && b1 == 1 ) || ( a1 == 1 && b1 == 0 ) ) && remainder == 0 )
		{
			remainder = 0;
			result.data[block] = 1 << bitPos | result.data[block];
			continue;
		}

	}

	return result;

}

QInt QInt::operator-(const QInt &A)
{
	QInt result = (QInt) A;
	result = ( *this ) + ( ~result + *( new QInt(10, "1") ) );
	return result;
}

QInt QInt::operator*(const QInt &A)
{
	QInt temp;

	QInt result = *this;

	int k = 128;
	int Q = 0;

	while ( k > 0 )
	{
		if ( int(result.data[3] & 1) == 1 && Q == 0 )
		{
			temp = temp - A;
		}
		if ( ( int(result.data[3] & 1) == 0 ) && ( Q == 1 ) )
		{
			temp = temp + A;
		}

		Q = result.data[3] & 1;
		result = result >> 1;

		if ( int(temp.data[3] & 1) == 1 )
		{
			result.data[0] = result.data[0] | ( 1 << 31 );
		}
		temp = temp >> 1;
		if ( Q == 1 )
			temp.data[0] = temp.data[0] | ( 1 << 31 );
		k--;

	}

	return result;
}

QInt QInt::operator/(const QInt & A)
{
	QInt quotient;

	QInt result = ( *this ).Abs();

	QInt divisor = ( (QInt) A ).Abs();

	if ( int(result.data[0] >> 31 & 1) == 1 )
	{
		quotient.data[0] = quotient.data[1] = quotient.data[2] = quotient.data[3] = UINT_MAX;
	}

	int k = 128;
	while ( k > 0 )
	{
		quotient = quotient << 1;

		if ( int(result.data[0] >> 31 & 1) == 1 )
			quotient.data[3] = quotient.data[3] | 1;

		result = result << 1;

		if ( int(divisor.data[0] >> 31 & 1) == 1 )
			quotient = quotient + divisor;
		else
			quotient = quotient - divisor;

		if ( int(quotient.data[0] >> 31 & 1) == 1 )
		{
			if ( int(divisor.data[0] >> 31 & 1) == 1 )
			{
				quotient = quotient - divisor;
			}
			else
				quotient = quotient + divisor;
		}
		else
		{
			result.data[3] = result.data[3] | 1;
		}
		k--;
	}

	return result;
}

QInt QInt::operator&(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int block = i / 32;
		int bitPos = 31 - i % 32;

		if ( int(data[block] >> bitPos & 1) == 1 && int(A.data[block] >> bitPos & 1) == 1 )
		{
			result.data[block] = result.data[block] | 1 << bitPos;
		}
	}
	return result;
}

QInt QInt::operator|(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int block = i / 32;
		int bitPos = 31 - i % 32;

		if ( !( int(data[block] >> bitPos & 1) == 0 && int(A.data[block] >> bitPos & 1) == 0 ) )
		{
			result.data[block] = result.data[block] | 1 << bitPos;
		}
	}
	return result;
}

QInt QInt::operator^(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int block = i / 32;
		int bitPos = 31 - i % 32;
		if ( int(data[block] >> bitPos & 1) != int(A.data[block] >> bitPos & 1) )
		{
			result.data[block] = result.data[block] | 1 << bitPos;
		}
	}

	return result;
}

QInt QInt::operator~()
{
	for ( int i = 0; i < 4; i++ )
		data[i] = ~data[i];

	return ( *this );
}

QInt QInt::operator<<(unsigned int numOfBit)
{
	QInt result = *this;
	for ( int i = 0; i < numOfBit; i++ )
	{
		if ( ( result.data[1] >> 31 ) == 1 )
		{
			result.data[0] <<= 1;
			result.data[0] += 1;
		}
		else
			result.data[0] <<= 1;

		if ( ( result.data[2] >> 31 ) == 1 )
		{
			result.data[1] <<= 1;
			result.data[1] += 1;
		}
		else
			result.data[1] <<= 1;

		if ( ( result.data[3] >> 31 ) == 1 )
		{
			result.data[2] <<= 1;
			result.data[2] += 1;
		}
		else
			result.data[2] <<= 1;

		result.data[3] <<= 1;
	}
	return result;
}

QInt QInt::operator >> (unsigned int numOfBit)
{
	QInt result = *this;

	for ( int i = 0; i < numOfBit; i++ )
	{
		if ( int(result.data[2] & 1) == int(1) )
		{
			result.data[3] >>= 1;
			result.data[3] = result.data[3] | ( 1 << 31 );
		}
		else
			result.data[3] >>= 1;

		if ( result.data[1] & 1 == 1 )
		{
			result.data[2] >>= 1;
			result.data[2] = result.data[2] | ( 1 << 31 );
		}
		else
			result.data[2] >>= 1;

		if ( result.data[0] & 1 == 1 )
		{
			result.data[1] >>= 1;
			result.data[1] = result.data[1] | ( 1 << 31 );
		}
		else
			result.data[1] >>= 1;

		result.data[0] >>= 1;
	}
	return result;

}