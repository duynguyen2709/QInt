#include "Utilities.h"

void ScanQInt(QInt & x)
{
	freopen("CON", "rt", stdin);

	cout << "Enter QInt number :";
	string number;
	getline(cin, number);
	x = *( new QInt(10, number) );
}

void PrintQInt(QInt x)
{
	string result = "0";

	bool * arr = DecToBin(x);
	string binary = "";
	for ( int i = 0; i < MAX_BIT_LENGTH; i++ )
	{
		binary += ( arr[i] == 1 ) ? "1" : "0";
	}

	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		if ( binary[i] == '1' )
			result = Add(result, MultiplyByTwo("1", MAX_BIT_LENGTH - i - 1));
	}

	cout << result;
}

bool * DecToBin(QInt x)
{
	int dem = 3;
	int tmp = MAX_BIT_LENGTH - 1;
	bool* result = new bool[MAX_BIT_LENGTH];
	while ( dem >= 0 )
	{
		int dem1 = 31;
		while ( dem1 >= 0 )
		{
			result[tmp] = ( x.data[dem] >> ( 31 - dem1 ) & 1 );
			tmp--;
			dem1--;
		}
		dem--;
	}
	return result;
}

QInt BinToDec(bool * bit)
{
	int dem = 0;
	int i = 0;
	QInt result;
	if ( Length(bit) < MAX_BIT_LENGTH )
	{
		bool* tmp = new bool[MAX_BIT_LENGTH];
		int j;
		for ( j = 0; j < MAX_BIT_LENGTH - Length(bit); j++ )
		{
			tmp[j] = 0;
		}
		for ( int z = 0; z < Length(bit); z++ )
		{
			tmp[j] = bit[z];
			j++;
		}
		bit = tmp;
	}
	while ( dem < 4 )
	{
		int dem1 = 0;
		while ( dem1 < 32 )
		{
			result.data[dem] = result.data[dem] | bit[i] << ( 31 - dem1 );
			dem1++;
			i++;
		}
		dem++;
	}
	return result;
}

char * BinToHex(bool * bit)
{
	char* result = new char[32];
	bool Flag = 0;
	int dem = 0;
	if ( Length(bit) < MAX_BIT_LENGTH )
	{
		bool* tmp = new bool[MAX_BIT_LENGTH];
		int j;
		for ( j = 0; j < MAX_BIT_LENGTH - Length(bit); j++ )
		{
			tmp[j] = 0;
		}
		for ( int z = 0; z < Length(bit); z++ )
		{
			tmp[j] = bit[z];
			j++;
		}
		bit = tmp;
	}
	int i = 0;
	while ( i < MAX_BIT_LENGTH )
	{
		int tmp = 0;
		for ( int j = 0; j < 4; j++ )
		{
			tmp += bit[i] * pow(2, 3 - j);
			i++;
		}
		switch ( tmp )
		{
			case 0:
				if ( Flag == 0 ) break;
				else
				{
					result[dem] = '0';
					dem++;
				}
				break;
			case 1:
				result[dem] = '1';
				dem++;
				Flag = 1;
				break;
			case 2:
				result[dem] = '2';
				dem++;
				Flag = 1;
				break;
			case 3:
				result[dem] = '3';
				dem++;
				Flag = 1;
				break;
			case 4:
				result[dem] = '4';
				dem++;
				Flag = 1;
				break;
			case 5:
				result[dem] = '5';
				dem++;
				Flag = 1;
				break;
			case 6:
				result[dem] = '6';
				dem++;
				Flag = 1;
				break;
			case 7:
				result[dem] = '7';
				dem++;
				Flag = 1;
				break;
			case 8:
				result[dem] = '8';
				dem++;
				Flag = 1;
				break;
			case 9:
				result[dem] = '9';
				dem++;
				Flag = 1;
				break;
			case 10:
				result[dem] = 'A';
				dem++;
				Flag = 1;
				break;
			case 11:
				result[dem] = 'B';
				dem++;
				Flag = 1;
				break;
			case 12:
				result[dem] = 'C';
				dem++;
				Flag = 1;
				break;
			case 13:
				result[dem] = 'D';
				dem++;
				Flag = 1;
				break;
			case 14:
				result[dem] = 'E';
				dem++;
				Flag = 1;
				break;
			case 15:
				result[dem] = 'F';
				dem++;
				Flag = 1;
				break;
		}
	}
	result[dem] = '\0';
	return result;
}

char * DecToHex(QInt x)
{
	return BinToHex(DecToBin(x));
}

QInt HexToDec(char * hex)
{
	return BinToDec(HexToBin(hex));
}

bool* HexToBin(char* hex)
{
	int dem = 0;
	while ( hex[dem] != '\0' )
	{
		dem++;
	}
	bool* result = new bool[dem * 4];
	int i = 0;
	int index = 0;
	while ( i < dem )
	{
		if ( hex[i] == '0' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == '1' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == '2' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == '3' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == '4' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == '5' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == '6' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == '7' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == '8' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == '9' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == 'A' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == 'B' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == 'C' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == 'D' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 1;
			index = index + 4;
		}
		if ( hex[i] == 'E' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 0;
			index = index + 4;
		}
		else if ( hex[i] == 'F' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 1;
			index = index + 4;
		}
		i++;
	}
	return result;
}

//--------------------------------------------------------------
int Length(bool* arr)
{
	int i = 0;
	while ( arr[i] == 0 || arr[i] == 1 )
	{
		i++;
	}
	return i;
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

bool * StringToBinary(string binaryString)
{
	bool * result = new bool[binaryString.length()];

	for ( int i = 0; i < binaryString.length(); i++ )
	{
		if ( (char) binaryString[i] == '1' )
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

	_fcloseall();
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

int CharToNum(char c)
{
	return c - '0';
}

string AddDigit0(int length)
{
	string str = "";
	for ( int i = 0; i < length; i++ )
		str += "0";
	return str;
}

string Add(string numberA, string numberB)
{
	string result = "";

	int lengthA = numberA.length();
	int lenghtB = numberB.length();

	if ( lengthA < lenghtB )
		numberA = AddDigit0(lenghtB - lengthA) + numberA;
	else
		numberB = AddDigit0(lengthA - lenghtB) + numberB;

	lengthA = lenghtB = numberA.length();
	bool remainder = false;

	for ( int i = lengthA - 1; i >= 0; i-- )
	{
		int c = CharToNum(numberA[i]) + CharToNum(numberB[i]);

		if ( remainder )
			c += 1;

		if ( c >= 10 )
		{
			remainder = true;
			c %= 10;
		}
		else remainder = false;

		result = (char) ( c + '0' ) + result;
	}

	if ( remainder )
		result = "1" + result;

	return result;
}

string MultiplyByTwo(string number, int times)
{
	for ( int i = 0; i < times; i++ )
	{
		number = Add(number, number);
	}
	return number;
}

string DataToDec(QInt A)
{
	string result = "0";

	//convert to binary
	bool * arr = DecToBin(A);
	string binary = "";
	for ( int i = 0; i < MAX_BIT_LENGTH; i++ )
	{
		binary += ( arr[i] == 1 ) ? "1" : "0";
	}

	//convert to big int
	for ( int i = MAX_BIT_LENGTH - 1; i >= 0; i-- )
	{
		if ( binary[i] == '1' )
			result = Add(result, MultiplyByTwo("1", MAX_BIT_LENGTH - i - 1));
	}
	return result;

}