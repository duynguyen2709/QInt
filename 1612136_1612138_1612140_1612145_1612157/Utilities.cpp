#include "Utilities.h"

void ScanQInt(QInt & x)
{
	cout << "Enter QInt number :";
	string number;
	getline(cin, number);
	x = *( new QInt(10, number) );
}

void PrintQInt(QInt x)
{}

bool * DecToBin(QInt x)
{
	return nullptr;
}

QInt BinToDec(bool * bit)
{
	return QInt();
}

char * BinToHex(bool * bit)
{
	return nullptr;
}

char * DecToHex(QInt x)
{
	return nullptr;
}

//--------------------------------------------------------------

int CharToNum(char c)
{
	return c - '0';
}

int CheckOddDigit(char c)
{
	return ( c == '1' || c == '3' || c == '5' || c == '7' || c == '9' ) ? 1 : 0;
}

string DivideByTwo(string str)
{
	string result = "";

	int add = 0;

	for ( auto c : str )
	{
		int newDigit = CharToNum(c) / 2 + add;

		result += (char) ( newDigit + '0' );

		add = CheckOddDigit(c) * 5;
	}

	if ( result != "0" )
	{
		//trim 0 at first
		int pos = result.find_first_not_of('0');

		result = result.substr(pos);
	}

	return result;
}

string DecToBin(string str)
{
	string result = "";

	if ( str == "0" )
		return "0";
	else
	{
		result = "";
		while ( str != "0" )
		{
			int binary = CheckOddDigit(str[str.length() - 1]);

			result = (char) ( binary + '0' ) + result;

			str = DivideByTwo(str);
		}
	}
	return result;

}

bool * StringToBinary(string str)
{
	bool * result = new bool[str.length()];

	for ( int i = 0; i < str.length(); i++ )
	{
		if ( (char) str[i] == '1' )
			result[i] = 1;
		else result[i] = 0;
	}

	return result;
}

void FileProcess(string inputFile)
{
	freopen(inputFile.c_str(), "rt", stdin);

	while ( !cin.eof() )
	{
		string str;
		getline(cin, str);

		QInt result = InputProcess(str);

		//PrintQInt(result);
	}
}

QInt Calculate(QInt A, QInt B, string operatorType)
{
	QInt result;

	if ( operatorType == "+" )
	{
		result = A + B;
	}
	else if ( operatorType == "-" )
	{
		result = A - B;
	}
	else if ( operatorType == "*" )
	{
		result = A * B;
	}
	else if ( operatorType == "/" )
	{
		result = A / B;
	}
	else if ( operatorType == "&" )
	{
		result = A & B;
	}
	else if ( operatorType == "|" )
	{
		result = A | B;
	}
	else if ( operatorType == "^" )
	{
		result = A ^ B;
	}
	else if ( operatorType == ">>" )
	{
		result = A >> B;
	}
	else if ( operatorType == "<<" )
	{
		result = A << B;
	}
	return result;
}

QInt InputProcess(string str)
{
	QInt result;
	int spaceCount = std::count(str.begin(), str.end(), ' ');

	size_t firstSpace = str.find_first_of(' ');
	size_t secondSpace = str.find(' ', firstSpace + 1);

	int p1 = stoi(str.substr(0, firstSpace));

	if ( spaceCount == 2 )
	{
		//converting from base p1 to p2
		int p2 = stoi(str.substr(firstSpace + 1, secondSpace - firstSpace - 1));

		string number = str.substr(secondSpace + 1);

		QInt A(p1, number);

	}
	else
	{
		//calculate with operator
		size_t thirdSpace = str.find(' ', secondSpace + 1);

		string numberA = str.substr(firstSpace + 1, secondSpace - firstSpace - 1);
		string numberB = str.substr(thirdSpace + 1);

		string operatorType = str.substr(secondSpace + 1, thirdSpace - secondSpace - 1);

		QInt A(p1, numberA);
		QInt B(p1, numberB);

		result = Calculate(A, B, operatorType);
	}
	return result;

}