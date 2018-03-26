#include "Utilities.h"

void Utilities::ScanQInt(QInt & x)
{
	freopen("CON", "rt", stdin);

	cout << "Enter QInt number :";
	string number;
	getline(cin, number);
	x = *( new QInt(10, number) );
}

void Utilities::PrintQInt(QInt x)
{
	string result = "0";

	bool * arr = DecToBin(x);

	string binary = "";

	for ( int i = 0; i < MAX_BIT_LENGTH; i++ )
	{
		binary += ( arr[i] == 1 ) ? "1" : "0";
	}

	for ( int i = MAX_BIT_LENGTH - 1; i > 0; i-- )
	{
		if ( binary[i] == '1' )
			result = Add(result, MultiplyByTwo("1", MAX_BIT_LENGTH - i - 1));
	}

	//Check negative
	result = ( ( arr[0] == 1 ) ? "-" : "" ) + result;

	cout << result;
}

bool * Utilities::DecToBin(QInt x)
{
	int dataPos = 3;

	int tmp = MAX_BIT_LENGTH - 1;

	bool* result = new bool[MAX_BIT_LENGTH];
	while ( dataPos >= 0 )
	{
		int bitPos = 31;
		while ( bitPos >= 0 )
		{
			result[tmp] = ( x.data[dataPos] >> ( 31 - bitPos ) & 1 );
			tmp--;
			bitPos--;
		}
		dataPos--;
	}
	return result;
}

QInt Utilities::BinToDec(bool * bit)
{
	int dataPos = 0;
	int i = 0;
	QInt result;

	if ( LengthOfBoolArray(bit) < MAX_BIT_LENGTH )
	{
		bool* tmp = new bool[MAX_BIT_LENGTH];
		int j;
		for ( j = 0; j < MAX_BIT_LENGTH - LengthOfBoolArray(bit); j++ )
		{
			tmp[j] = 0;
		}
		for ( int z = 0; z < LengthOfBoolArray(bit); z++ )
		{
			tmp[j] = bit[z];
			j++;
		}
		bit = tmp;
	}
	while ( dataPos < 4 )
	{
		int bitPos = 0;
		while ( bitPos < 32 )
		{
			result.data[dataPos] = result.data[dataPos] | bit[i] << ( 31 - bitPos );
			bitPos++;
			i++;
		}
		dataPos++;
	}
	return result;
}

char * Utilities::BinToHex(bool * bit)
{
	char* result = new char[32];
	bool flag = 0;
	int count = 0;
	if ( LengthOfBoolArray(bit) < MAX_BIT_LENGTH )
	{
		bool* tmp = new bool[MAX_BIT_LENGTH];
		int j;
		for ( j = 0; j < MAX_BIT_LENGTH - LengthOfBoolArray(bit); j++ )
		{
			tmp[j] = 0;
		}
		for ( int z = 0; z < LengthOfBoolArray(bit); z++ )
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
				if ( flag == 0 ) break;
				result[count++] = tmp + '0';
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				result[count++] = tmp + '0';
				break;
			case 10:
				result[count++] = 'A';
				break;
			case 11:
				result[count++] = 'B';
				break;
			case 12:
				result[count++] = 'C';
				break;
			case 13:
				result[count++] = 'D';
				break;
			case 14:
				result[count++] = 'E';
				break;
			case 15:
				result[count++] = 'F';
				break;
		}
		if ( tmp != 0 )
			flag = 1;
	}
	result[count] = '\0';
	return result;
}

char * Utilities::DecToHex(QInt x)
{
	return BinToHex(DecToBin(x));
}

QInt Utilities::HexToDec(char * hex)
{
	return BinToDec(HexToBin(hex));
}

bool* Utilities::HexToBin(char* hex)
{
	int count = 0;
	while ( hex[count] != '\0' )
	{
		count++;
	}
	bool* result = new bool[count * 4];
	int i = 0;
	int index = 0;
	while ( i < count )
	{
		if ( hex[i] == '0' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 0;

		}
		else if ( hex[i] == '1' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 1;

		}
		if ( hex[i] == '2' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 0;

		}
		else if ( hex[i] == '3' )
		{
			result[index] = 0;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 1;

		}
		if ( hex[i] == '4' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 0;

		}
		else if ( hex[i] == '5' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 1;

		}
		if ( hex[i] == '6' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 0;

		}
		else if ( hex[i] == '7' )
		{
			result[index] = 0;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 1;

		}
		if ( hex[i] == '8' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 0;

		}
		else if ( hex[i] == '9' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 0;
			result[index + 3] = 1;

		}
		if ( hex[i] == 'A' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 0;

		}
		else if ( hex[i] == 'B' )
		{
			result[index] = 1;
			result[index + 1] = 0;
			result[index + 2] = 1;
			result[index + 3] = 1;

		}
		if ( hex[i] == 'C' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 0;

		}
		else if ( hex[i] == 'D' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 0;
			result[index + 3] = 1;

		}
		if ( hex[i] == 'E' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 0;

		}
		else if ( hex[i] == 'F' )
		{
			result[index] = 1;
			result[index + 1] = 1;
			result[index + 2] = 1;
			result[index + 3] = 1;

		}
		index += 4;
		i++;
	}
	return result;
}

/*----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//-- UTILITIES FUNCTIONS
//----------------------------------------------------------------------------
----------------------------------------------------------------------------*/

int Utilities::LengthOfBoolArray(bool* arr)
{
	int i = 0;
	while ( arr[i] == 0 || arr[i] == 1 )
	{
		i++;
	}
	return i;
}

string Utilities::BoolArrayToString(bool *arr, int length)
{
	string result = "";
	for ( int i = 0; i < length; i++ )
	{
		if ( arr[i] == 1 )
			result += "1";
		else result += "0";
	}
	return result;
}

int Utilities::CharToNum(char c)
{
	return c - '0';
}

int Utilities::CheckOddDigit(char c)
{
	return ( c == '1' || c == '3' || c == '5' || c == '7' || c == '9' ) ? 1 : 0;
}

string Utilities::Trim0AtFirst(string binary)
{
	if ( binary != "0" )
	{
		int pos = binary.find_first_of('1');
		if ( pos != string::npos )
		{
			binary = binary.substr(pos);
		}
	}
	return binary;
}

string Utilities::DivideByTwo(string str)
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

string Utilities::DecToBin(string str)
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

bool * Utilities::StringToBinary(string binaryString)
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

void Utilities::FileProcess(string inputFile)
{
	freopen(inputFile.c_str(), "rt", stdin);

	while ( !cin.eof() )
	{
		string str;
		getline(cin, str);

		cout << InputProcess(str) << endl;

	}

	_fcloseall();
}

string Utilities::Convert(int p1, int p2, string number)
{
	QInt A(p1, number);

	string result = "";

	switch ( p1 )
	{
		case 2:
			if ( p2 == 10 )
				result = DataToDec(A);
			else if ( p2 == 16 )
				result = BinToHex(DecToBin(A));
			break;

		case 10:
			if ( p2 == 2 )
				result = Trim0AtFirst(BoolArrayToString(DecToBin(A), LengthOfBoolArray(DecToBin(A))));
			else if ( p2 == 16 )
				result = DecToHex(A);
			break;

		case 16:
			if ( p2 == 2 )
			{
				char *hex = DecToHex(A);
				result = Trim0AtFirst(BoolArrayToString(HexToBin(hex), LengthOfBoolArray(HexToBin(hex))));

			}
			else if ( p2 == 10 )
				result = DataToDec(A);
			break;

	}

	return result;
}

string Utilities::InputProcess(string str)
{
	string result = "";

	int spaceCount = std::count(str.begin(), str.end(), ' ');

	size_t firstSpace = str.find_first_of(' ');
	size_t secondSpace = str.find(' ', firstSpace + 1);

	int p1 = stoi(str.substr(0, firstSpace));

	if ( spaceCount == 2 )
	{
		//converting from base p1 to p2
		int p2 = stoi(str.substr(firstSpace + 1, secondSpace - firstSpace - 1));

		string number = str.substr(secondSpace + 1);

		result = Convert(p1, p2, number);
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
		QInt temp;

		if ( operatorType == "<<" )
		{
			int bit = stoi(numberB);
			temp = A << bit;
		}
		else if ( operatorType == ">>" )
		{
			int bit = stoi(numberB);
			temp = A >> bit;
		}
		else temp = Calculate(A, B, operatorType);

		//convert QInt to Base p1
		switch ( p1 )
		{
			case 2:
				result = Trim0AtFirst(BoolArrayToString(DecToBin(temp), LengthOfBoolArray(DecToBin(temp))));
				break;
			case 10:
				result = DataToDec(temp);
				break;
			case 16:
				result = DecToHex(temp);
				break;
		}
	}
	return result;
}

QInt Utilities::Calculate(QInt A, QInt B, string operatorType)
{
	QInt result;

	if ( operatorType == "+" )
	{
		if ( A.isNegative() && !B.isNegative() )
		{
			if ( A.Abs() > B )
			{
				result = A.Abs() - B;
				result.data[0] = ( 1 << 31 ) | result.data[0];
			}
			else result = B - A.Abs();
		}
		else if ( !A.isNegative() && B.isNegative() )
		{
			if ( B.Abs() > A )
			{
				result = B.Abs() - A;
				result.data[0] = ( 1 << 31 ) | result.data[0];
			}
			else
				result = A - B.Abs();
		}
		else if ( A.isNegative() && B.isNegative() )
		{
			result = A + B;
			result.data[0] = ( 1 << 31 ) | result.data[0];
		}
		else
			result = A + B;

	}
	else if ( operatorType == "-" )
	{
		if ( A == B )
			return QInt(10, "0");

		QInt result = B;

		bool is_B_Negative = ( (QInt) B ).isNegative();

		bool is_A_Negative = A.isNegative();

		// (A > 0 && A < 0)
		if ( !is_A_Negative && is_B_Negative )
		{
			result = result.Abs() + A;
		}

		// (A < 0 && A > 0)
		else if ( is_A_Negative && !is_B_Negative )
		{
			result = result + A.Abs();

			result.data[0] = ( 1 << 31 ) | result.data[0];
		}

		// (A > 0 && A > 0)
		else if ( !is_A_Negative && !is_B_Negative )
		{
			if ( A > B )
			{
				result = A + ( ~result + *( new QInt(10, "1") ) );
			}
			else
			{
				result = result - A;
				result.data[0] = ( 1 << 31 ) | result.data[0];
			}
		}

		// (A < 0 && A < 0)
		else
		{
			if ( A > B )
			{
				result = result.Abs() - A.Abs();
			}
			else
			{
				result = A.Abs() - result.Abs();
				result.data[0] = ( 1 << 31 ) | result.data[0];
			}
		}

		return result;

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

	return result;
}

string Utilities::AddDigit0(int length)
{
	string str = "";
	for ( int i = 0; i < length; i++ )
		str += "0";
	return str;
}

string Utilities::Add(string numberA, string numberB)
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

string Utilities::MultiplyByTwo(string number, int times)
{
	for ( int i = 0; i < times; i++ )
	{
		number = Add(number, number);
	}
	return number;
}

string Utilities::DataToDec(QInt A)
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
	for ( int i = MAX_BIT_LENGTH - 1; i > 0; i-- )
	{
		if ( binary[i] == '1' )
			result = Add(result, MultiplyByTwo("1", MAX_BIT_LENGTH - i - 1));
	}

	result = ( ( arr[0] == 1 ) ? "-" : "" ) + result;

	return result;

}