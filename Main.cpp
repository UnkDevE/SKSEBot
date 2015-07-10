#include "BaseAuRegClass.h"
#include <iostream>

int main() 
{
	std::cout << "namespace Y, class N" << std::endl;
	char YorN;
	std::cin >> YorN;

	std::cout << "header file name :" << std::endl;
	std::string HeaderFile;
	std::cin >> HeaderFile;

	std::cout << "outputFile name" << std::endl;
	std::string OutFile;
	std::cin >> OutFile;

	AutoRegister a(HeaderFile, OutFile);

	if(YorN != 'Y'){
		std::cout << "Namespace output filename" << std::endl;
		std::string NoF;
		std::cin >> NoF;
		a.CreateClassSelfunctions(NoF);
	}

	std::cout << "Do you want to generate SetFunctionFlags Functions ? Y/N" << std::endl;
	std::cin >> YorN;

	if (YorN == 'Y') {
		std::cout << "function flag (please leave out VMRegistry::) X for kFunctionFlag_NoWait" << std::endl;
		std::string FuncFlag;
		std::cin >> FuncFlag;
		if (FuncFlag == "X")a.CreateSetFunctionFlags();
		else a.CreateSetFunctionFlags(FuncFlag);
	}
}
