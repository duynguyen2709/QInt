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
{}

bool QInt::operator==(const QInt & A)
{
	for ( int i = 3; i >= 0; i-- )
	{
		if ( A.data[i] != data[i] )
			return false;
	}
	return true;
}

QInt QInt::operator+(const QInt & A)
{
	QInt result;

	int nho = 0;
	for ( int i = 0; i < 32 * 4; i++ )
	{
		int o = 3 - i / 32;
		int k = i % 32;
		int a1, b1;
		a1 = A.data[o] >> k & 1;
		b1 = data[o] >> k & 1;
		if ( ( i == 127 ) && ( nho + a1 + b1 >= 2 ) )
		{
			cout << "Stackoverflow!!!!!!!";
		}

		if ( a1 == 0 && b1 == 0 && ( nho == 1 ) )
		{
			nho = 0;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}

		if ( a1 == 0 && b1 == 0 && ( nho == 1 ) )
		{
			nho = 1;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}
		if ( a1 == 1 && b1 == 1 && ( nho == 0 ) )
		{
			nho = 1;
			result.data[o] = 0 << k | result.data[o];
			continue;
		}
		if ( a1 == 1 && b1 == 1 && ( nho == 1 ) )
		{
			nho = 1;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}
		if ( ( ( a1 == 0 && b1 == 1 ) || ( a1 == 1 && b1 == 0 ) ) && nho == 1 )
		{
			nho = 1;
			result.data[o] = 0 << k | result.data[o];
			continue;
		}
		if ( ( ( a1 == 0 && b1 == 1 ) || ( a1 == 1 && b1 == 0 ) ) && nho == 0 )
		{
			nho = 0;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}

	}

	return result;

}

QInt QInt::operator-(const QInt & A)
{
	QInt result;
	QInt notA = A;
	~notA;
	QInt add1(10, "1");
	notA = notA + add1;
	result = *this + notA;
	return result;

}

QInt QInt::operator*(const QInt & A)
{
	return QInt();
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