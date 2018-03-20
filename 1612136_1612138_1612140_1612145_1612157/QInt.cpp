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
		*this = SplitNumber(A.DecToBin(num));
	}
	else if ( base == 2 )
	{
		*this = A.BinToDec(A.StringToBinary(num));
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
	return QInt();
}

QInt QInt::operator-(const QInt & A)
{
	return QInt();
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
	return QInt();
}

QInt QInt::operator<<(const QInt & A)
{
	return QInt();
}

QInt QInt::operator >> (const QInt & A)
{
	return QInt();
}