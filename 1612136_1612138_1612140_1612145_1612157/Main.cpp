#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	QInt::InitializeLimits();

	Utilities MainController;

	MainController.FileProcess("INPUT2.TXT");

	cout << endl;
	return 0;
}