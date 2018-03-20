#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#pragma once
#include <iostream>
#include <string>
#include "QInt.h"

using namespace std;

#define MAX_BIT_LENGTH 128

class QInt;

class Utilities
{
public:
	Utilities()
	{};
	~Utilities()
	{};

	//************************************
	// Method:    FileProcess
	// Returns:   void
	// Parameter: string inputFile
	// Using :    Handling Input File
	//************************************
	void FileProcess(string inputFile);

	//************************************
	// Method:    ScanQInt
	// Returns:   void
	// Parameter: QInt & x
	// Using :    Get input to a QInt
	//************************************
	void ScanQInt(QInt &x);

	//************************************
	// Method:    PrintQInt
	// Returns:   void
	// Parameter: QInt x
	// Using :    Print a QInt
	//************************************
	void PrintQInt(QInt x);

	//************************************
	// Method:    DecToBin
	// Returns:   bool *
	// Parameter: QInt x
	// Using :   Convert QInt/Decimal to Array of Boolean
	//************************************
	bool * DecToBin(QInt x);

	//************************************
	// Method:    BinToDec
	// Returns:   QInt
	// Parameter: bool * bit
	// Using :    Convert Array of Bits to Decimal/QInt
	//************************************
	QInt BinToDec(bool *bit);

	//************************************
	// Method:    BinToHex
	// Returns:   char *
	// Parameter: bool * bit
	// Using :    Convert Array of Bits to Hexadecimal
	//************************************
	char * BinToHex(bool *bit);

	//************************************
	// Method:    DecToHex
	// Returns:   char *
	// Parameter: QInt x
	// Using :    Convert Decimal/QInt to Hexadecimal
	//************************************
	char * DecToHex(QInt x);

	//************************************
	// Method:    HexToDec
	// Returns:   QInt
	// Parameter: char * hex
	// Using :    Convert Hexadecimal to Decimal/QInt
	//************************************
	QInt HexToDec(char *hex);

	//************************************
	// Method:    HexToBin
	// Returns:   bool*
	// Parameter: char * hex
	// Using :    Convert hexadecimal to Array of Boolean
	//************************************
	bool* HexToBin(char* hex);

private:

	//----------------------------------------------------------------------------
	//-- UTILITIES FUNCTIONS
	//----------------------------------------------------------------------------

	//************************************
	// Method:    InputProcess
	// Returns:   std::string
	// Parameter: string str
	// Using :    Process each line of input (converting/calculating)
	//************************************
	string InputProcess(string str);

	//************************************
	// Method:    Convert
	// Returns:   std::string
	// Parameter: int p1
	// Parameter: int p2
	// Parameter: string number
	// Using :    Convert number in Base p1 to Base p2
	//************************************
	string Convert(int p1, int p2, string number);

	//************************************
	// Method:    LengthOfBoolArray
	// Returns:   int
	// Parameter: bool * arr
	// Using :    return length of Boolean Array
	//************************************
	int LengthOfBoolArray(bool* arr);

	//************************************
	// Method:    BoolArrayToString
	// Returns:   std::string
	// Parameter: bool * arr
	// Parameter: int length
	// Using :    Convert Bool Array to String
	//************************************
	string BoolArrayToString(bool *arr, int length);

	//************************************
	// Method:    CharToNum
	// Returns:   int
	// Parameter: char c
	// Using :    Return the value of c in integer
	//************************************
	int CharToNum(char c);

	//************************************
	// Method:    CheckOddDigit
	// Returns:   int (1/0)
	// Parameter: char c
	// Using :    Check if c is odd digit
	//************************************
	int CheckOddDigit(char c);

	//************************************
	// Method:    Trim0AtFirst
	// Returns:   std::string
	// Parameter: string binary
	// Using :    Trim Digit 0 at First of Binary String
	//************************************
	string Trim0AtFirst(string binary);

	//************************************
	// Method:    DivideByTwo
	// Returns:   std::string
	// Parameter: string str
	// Using :    Divide big integer by 2
	//************************************
	string DivideByTwo(string str);

	//************************************
	// Method:    DecToBin
	// Returns:   std::string
	// Parameter: string str
	// Using :    Convert Decimal to Binary string
	//************************************
	string DecToBin(string str);

	//************************************
	// Method:    StringToBinary
	// Returns:   bool *
	// Parameter: string str
	// Using :    Convert Binary string to Array of Bits
	//************************************
	bool * StringToBinary(string str);

	//************************************
	// Method:    Calculate
	// Returns:   QInt
	// Parameter: QInt A
	// Parameter: QInt B
	// Parameter: string operatorType
	// Using :    A "operator" B
	//************************************
	QInt Calculate(QInt A, QInt B, string operatorType);

	//************************************
	// Method:    AddDigit0
	// Returns:   std::string
	// Parameter: int length
	// Using :    Add 'length' Digit 0 at First of Binary String
	//************************************
	string AddDigit0(int length);

	string Add(string numberA, string numberB);

	string MultiplyByTwo(string number, int times);

	string DataToDec(QInt A);

	friend class QInt;
};

#endif // !_UTILITIES_H_