#include "Utilities.h"
#include "QInt.h"

using namespace std;

void PrintBoolArray(bool *arr, int length)
{
	for ( int i = 0; i < length; i++ )
	{
		if ( arr[i] == 1 )
			cout << 1;
		else cout << 0;
	}
	cout << endl;
}
int main()
{
	//FileProcess("INPUT.TXT");

	QInt A(2, "111010110111100110100010101");
	cout << DataToDec(A) << endl;
	return 0;
}