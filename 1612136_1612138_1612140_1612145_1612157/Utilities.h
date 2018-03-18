#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#pragma once
#include <iostream>
#include <string>
#include "QInt.h"

using namespace std;
class QInt;

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

//----------------------------------------------------------------------------
//-- UTILITIES FUNCTIONS
//----------------------------------------------------------------------------

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
// Using :    Convert Big Integer to Binary string
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
// Method:    FileProcess
// Returns:   void
// Parameter: string inputFile
// Using :    Handling Input File
//************************************
void FileProcess(string inputFile);

//************************************
// Method:    InputProcess
// Returns:   QInt
// Parameter: string str
// Using :    Process each case of input (converting / calculating)
//************************************
QInt InputProcess(string str);

//************************************
// Method:    Calculate
// Returns:   QInt
// Parameter: QInt A
// Parameter: QInt B
// Parameter: string operatorType
// Using :    A "operator" B
//************************************
QInt Calculate(QInt A, QInt B, string operatorType);

#endif // !_UTILITIES_H_