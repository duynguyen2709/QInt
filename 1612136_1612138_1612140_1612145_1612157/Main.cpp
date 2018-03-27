#include "Utilities.h"
#include "QInt.h"
using namespace std;

int main(int argc, char **argv)
{
	Utilities MainController;
	Utilities::InitializeExpOfTwo();
	QInt::InitializeLimits();

	MainController.FileProcess(argv[1], argv[2]);

	return 0;
}