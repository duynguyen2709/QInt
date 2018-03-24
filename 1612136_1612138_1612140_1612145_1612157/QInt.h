#ifndef _QINT_H_
#define _QINT_H_
#pragma once

#include <iostream>
#include <bitset>
using namespace std;

class QInt
{
private:
	unsigned int data[4];

	//************************************
	// Method:    splitNumber
	// Returns:   QInt
	// Parameter: string binary
	// Using :    Split big integer to 4 32bit-integers
	//************************************
	QInt SplitNumber(string binary);

public:

	QInt();
	QInt(int base, string num);

	~QInt();
	bool operator==(const QInt &A);

	QInt operator+(const QInt &A);
	QInt operator-(const QInt &A);
	QInt operator*(const QInt &A);
	QInt operator/(const QInt &A);

	QInt operator&(const QInt &A);
	QInt operator|(const QInt &A);
	QInt operator^(const QInt &A);
	QInt operator~();

	QInt operator<<(unsigned int numOfBit);
	QInt operator >> (unsigned int numOfBit);

	friend class Utilities;
};

#endif