#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;
	MainController.FileProcess("INPUT.TXT");

	QInt A(2, "1001011010100101000100010111110");
	QInt B(10, "1263700158");

	if ( A == B )
		cout << "=" << endl;
	else cout << "!=" << endl;

	return 0;
}