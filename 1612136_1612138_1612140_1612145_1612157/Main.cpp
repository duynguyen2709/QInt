#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;

	MainController.FileProcess("INPUT2.TXT");

	/*QInt A(10, "139565786721589715");
	QInt B(10, "139565786762151");
	QInt C = A / B;
	MainController.PrintQInt(C);*/

	cout << endl;
	return 0;
}