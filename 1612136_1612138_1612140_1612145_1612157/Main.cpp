#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;

	//MainController.FileProcess("INPUT2.TXT");

	QInt A(10, "100");
	QInt B(10, "10");
	MainController.PrintQInt(A - B);
	return 0;
}