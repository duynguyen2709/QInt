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
	static QInt QINT_MAX;
	static QInt QINT_MIN;

	QInt();
	QInt(int base, string num);

	static void InitializeLimits();
	~QInt();

	bool isNegative();
	QInt Abs();

	bool operator==(const QInt &A);
	bool operator>(const QInt & A);

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