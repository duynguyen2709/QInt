#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;

	//MainController.FileProcess("INPUT.TXT");

//-----CÁC HÀM CẦN SỬ DỤNG NẰM TRONG MAINCONTROLLER

	QInt A(10, "28935791875196");
	QInt B(2, "1010101010");

	QInt C = A << 13;

	MainController.PrintQInt(C);

	cout << endl;

	return 0;
}