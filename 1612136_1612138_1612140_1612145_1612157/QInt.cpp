#include "QInt.h"
#include "Utilities.h"

QInt QInt::splitNumber(string binary)
{
	QInt result;

	int digit0 = 128 - binary.length();
	for ( int i = 0; i < digit0; i++ )
	{
		binary = "0" + binary;
	}

	string str = "";
	int k = 0;
	for ( int i = 1; i <= 128; i++ )
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
	number = "0";
}

QInt::QInt(int base, string num)
{
	if ( base == 10 )
	{
		*this = splitNumber(DecToBin(num));
	}
	else if ( base == 2 )
	{
		*this = splitNumber(num);
	}
	else if ( base == 16 )
	{
	}

}

QInt::~QInt()
{}

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