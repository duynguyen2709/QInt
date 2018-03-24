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
	return QInt();
}

QInt QInt::operator|(const QInt & A)
{
	return QInt();
}

QInt QInt::operator^(const QInt & A)
{
	return QInt();
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