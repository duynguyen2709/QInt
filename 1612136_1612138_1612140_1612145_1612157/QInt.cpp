#include "QInt.h"
#include "Utilities.h"

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

QInt::QInt()
{
	for ( size_t i = 0; i < 4; i++ )
	{
		data[i] = 0;
	}

}

QInt::QInt(int base, string num)
{
	Utilities A;

	for ( size_t i = 0; i < 4; i++ )
	{
		data[i] = 0;
	}
	if ( base == 10 )
	{
		if ( num[0] != '-' )
			*this = SplitNumber(A.DecToBin(num));
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

		else cout << "Overflow" << endl;
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
		}
	}

	return false;
}

QInt QInt::operator+(const QInt & A)
{
	QInt result;

	int remainder = 0;
	for ( int i = 0; i < MAX_BIT_LENGTH - 1; i++ )
	{
		int block = 3 - i / 32;
		int bitPos = i % 32;

		int a1, b1;
		a1 = A.data[block] >> bitPos & 1;
		b1 = data[block] >> bitPos & 1;

		if ( ( i == 127 ) && ( remainder + a1 + b1 >= 2 ) )
		{
			cout << "NUMBER OVERFLOW !";
			return QInt(10, "0");
		}

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

QInt QInt::operator-(const QInt & A)
{
	if ( *this == A )
		return QInt(10, "0");

	QInt result = A;

	bool is_A_Negative = ( (QInt) A ).isNegative();

	bool is_This_Negative = isNegative();

	// (*this > 0 && A < 0)
	if ( !is_This_Negative && is_A_Negative )
	{
		result = result.Abs() + ( *this );
	}

	// (*this < 0 && A > 0)
	else if ( is_This_Negative && !is_A_Negative )
	{
		result = result + ( *this ).Abs();

		result.data[0] = ( 1 << 31 ) | result.data[0];
	}

	// (*this > 0 && A > 0)
	else if ( !is_This_Negative && !is_A_Negative )
	{
		if ( *this > A )
		{
			result = ( *this ) + ( ~result + *( new QInt(10, "1") ) );
		}
		else
		{
			result = result - ( *this );
			result.data[0] = ( 1 << 31 ) | result.data[0];
		}
	}

	// (*this < 0 && A < 0)
	else
	{
		if ( *this > A )
		{
			result = result.Abs() - ( *this ).Abs();
		}
		else
		{
			result = ( *this ).Abs() - result.Abs();
			result.data[0] = ( 1 << 31 ) | result.data[0];
		}
	}

	return result;

}

QInt QInt::operator*(const QInt &A)
{
	QInt result;

	QInt temp = (QInt) A;

	int block = 3;
	int bitPos = 31;

	for ( int i = 0; i < MAX_BIT_LENGTH; i++ )
	{
		int bit = ( temp.data[block] >> ( 31 - bitPos ) ) & 1;
		if ( bit == 1 )
			result = result + ( ( *this ) << i );

		bitPos--;
		if ( bitPos < 0 )
		{
			block--;
			bitPos = 31;
		}
	}

	bool is_A_Negative = ( (QInt) A ).isNegative();
	bool is_This_Negative = isNegative();

	if ( ( is_A_Negative && is_This_Negative ) || ( !is_A_Negative && !is_This_Negative ) )
	{
		result = result.Abs();
	}
	else result.data[0] = ( 1 << 31 ) | result.data[0];

	return result;
}

QInt QInt::operator/(const QInt & A)
{
	return QInt();
}

QInt QInt::operator&(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int o = i / 32;
		int k = 31 - i % 32;
		if ( int(data[o] >> k & 1) == 1 && int(A.data[o] >> k & 1) == int(1) )
		{
			result.data[o] = result.data[o] | 1 << k;
		}
	}
	return result;
}

QInt QInt::operator|(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int o = i / 32;
		int k = 31 - i % 32;
		if ( !( int(data[o] >> k & 1) == 0 && int(A.data[o] >> k & 1) == 0 ) )
		{
			result.data[o] = result.data[o] | 1 << k;
		}
	}
	return result;
}

QInt QInt::operator^(const QInt & A)
{
	QInt result;

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		int o = i / 32;
		int k = 31 - i % 32;
		if ( int(data[o] >> k & 1) != int(A.data[o] >> k & 1) )
		{
			result.data[o] = result.data[o] | 1 << k;
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
	if ( numOfBit >= MAX_BIT_LENGTH )
		return QInt();

	QInt result = *this;

	for ( int i = 0; i < numOfBit; i++ )
	{
		int *firstBit = new int[3];
		int j = 0;

		for ( j = 1; j <= 3; j++ )
			firstBit[j] = ( result.data[j] >> 31 ) & 1;

		for ( j = 0; j < 4; j++ )
			result.data[j] <<= 1;

		for ( j = 1; j <= 3; j++ )
		{
			if ( firstBit[j] == 1 )
				result.data[j - 1] = 1 | result.data[j - 1];
		}
	}

	return result;
}

QInt QInt::operator >> (unsigned int numOfBit)
{
	if ( numOfBit >= MAX_BIT_LENGTH )
		return QInt();

	QInt result = *this;

	for ( int i = 0; i < numOfBit; i++ )
	{
		int *lastBit = new int[3];
		int j = 0;

		for ( j = 0; j < 3; j++ )
			lastBit[j] = result.data[j] & 1;

		for ( j = 0; j < 4; j++ )
			result.data[j] >>= 1;

		for ( j = 0; j < 3; j++ )
		{
			if ( lastBit[j] == 1 )
				result.data[j + 1] = ( 1 << 31 ) | result.data[j + 1];
		}
	}

	return result;
}