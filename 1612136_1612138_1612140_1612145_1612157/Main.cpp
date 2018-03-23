#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;

	//MainController.FileProcess("INPUT.TXT");

	QInt A(10, "28935791875196194");
	QInt B(10, "4736582683617");
	QInt C = A | B;
	MainController.PrintQInt(C);

	cout << endl;
	return 0;

}