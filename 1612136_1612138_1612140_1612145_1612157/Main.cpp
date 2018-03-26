#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	QInt::InitializeLimits();

	Utilities MainController;

	//MainController.FileProcess("INPUT2.TXT");

	/*QInt A(10, "139565786721589715");
	QInt B(10, "139565786762151");
	QInt C = A / B;
	MainController.PrintQInt(C);*/

	cout << endl;
	return 0;
}
/*
QInt QInt::operator-(const QInt & B)
{
	if ( A == B )
		return QInt(10, "0");

	QInt result = B;

	bool is_A_Negative = ( (QInt) B ).isNegative();

	bool is_This_Negative = isNegative();

	// (A > 0 && A < 0)
	if ( !is_This_Negative && is_A_Negative )
	{
		result = result.Abs() + ( A );
	}

	// (A < 0 && A > 0)
	else if ( is_This_Negative && !is_A_Negative )
	{
		result = result + ( A ).Abs();

		result.data[0] = ( 1 << 31 ) | result.data[0];
	}

	// (A > 0 && A > 0)
	else if ( !is_This_Negative && !is_A_Negative )
	{
		if ( A > B )
		{
			result = ( A ) + ( ~result + *( new QInt(10, "1") ) );
		}
		else
		{
			result = result - ( A );
			result.data[0] = ( 1 << 31 ) | result.data[0];
		}
	}

	// (A < 0 && A < 0)
	else
	{
		if ( A > B )
		{
			result = result.Abs() - ( A ).Abs();
		}
		else
		{
			result = ( A ).Abs() - result.Abs();
			result.data[0] = ( 1 << 31 ) | result.data[0];
		}
	}

	return result;

}*/