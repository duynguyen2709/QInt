#include "Utilities.h"
#include "QInt.h"

using namespace std;

int main()
{
	Utilities MainController;

	//MainController.FileProcess("INPUT.TXT");

//-----CÁC HÀM CẦN SỬ DỤNG NẰM TRONG MAINCONTROLLER

	QInt A(10, "28935791875196");
	QInt B(2, "01001000111001100010010100011111");
	QInt C = A << 40;

	MainController.PrintQInt(C);
	cout << endl;
	return 0;
}