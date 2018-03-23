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

	int remainder = 0;
	for ( int i = 0; i < 32 * 4; i++ )
	{
		int o = 3 - i / 32;
		int k = i % 32;

		int numA, numB;
		numA = A.data[o] >> k & 1;
		numB = data[o] >> k & 1;

		if ( ( i == MAX_BIT_LENGTH - 1 ) && ( remainder + numA + numB >= 2 ) )
		{
			cout << "Stackoverflow!!!!!!!";
		}

		if ( numA == 0 && numB == 0 && ( remainder == 1 ) )
		{
			remainder = 0;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}

		if ( numA == 0 && numB == 0 && ( remainder == 1 ) )
		{
			remainder = 1;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}
		if ( numA == 1 && numB == 1 && ( remainder == 0 ) )
		{
			remainder = 1;
			result.data[o] = 0 << k | result.data[o];
			continue;
		}
		if ( numA == 1 && numB == 1 && ( remainder == 1 ) )
		{
			remainder = 1;
			result.data[o] = 1 << k | result.data[o];
			continue;
		}
		if ( ( ( numA == 0 && numB == 1 ) || ( numA == 1 && numB == 0 ) ) && remainder == 1 )
		{
			remainder = 1;
			result.data[o] = 0 << k | result.data[o];
			continue;
		}
		if ( ( ( numA == 0 && numB == 1 ) || ( numA == 1 && numB == 0 ) ) && remainder == 0 )
		{
			remainder = 0;
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

QInt QInt::operator*(const QInt & b)
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

QInt QInt::operator<<(const QInt & A)
{
	return QInt();
}

QInt QInt::operator >> (const QInt & A)
{
	return QInt();
}