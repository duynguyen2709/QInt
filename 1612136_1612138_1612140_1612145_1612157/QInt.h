#ifndef _QINT_H_
#define _QINT_H_
#pragma once

#include <iostream>
#include <bitset>
using namespace std;

class QInt
{
private:
	_int32 data[4];
	string number;

	//************************************
	// Method:    splitNumber
	// Returns:   QInt
	// Parameter: string binary
	// Using :    Split binary string to 4 integer
	//************************************
	QInt splitNumber(string binary);

public:

	QInt();
	QInt(int base, string num);
	~QInt();

	QInt operator+(const QInt &A);
	QInt operator-(const QInt &A);
	QInt operator*(const QInt &A);
	QInt operator/(const QInt &A);

	QInt operator&(const QInt &A);
	QInt operator|(const QInt &A);
	QInt operator^(const QInt &A);
	QInt operator~();

	QInt operator<<(const QInt &A);
	QInt operator >> (const QInt &A);

};

#endif