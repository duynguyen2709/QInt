#include "Utilities.h"
#include "QInt.h"
using namespace std;

int main()
{
	Utilities MainController;
	Utilities::InitializeExpOfTwo();
	QInt::InitializeLimits();

	MainController.FileProcess("INPUT2.TXT");
	cout << endl;
	return 0;
}