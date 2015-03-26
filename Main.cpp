#include "BaseAuRegClass.h"
#include <iostream>
int main() {
	std::cout << "namespace Y, class N" << std::endl;
	char YorN;
	std::cin >> YorN;

	std::cout << "header file name :" << std::endl;
	std::string f;
	std::cin >> f;

	std::cout << "outputFile name" << std::endl;
	std::string b;
	std::cin >> b;

	if (YorN == 'Y')AutoRegister a(f, b);
	else{
		std::cout << "Namespace output filename" << std::endl;
		std::string NoF;
		std::cin >> NoF;
		AutoRegister a(f, b, NoF);
	}
}