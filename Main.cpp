#include "BaseAuRegClass.h"
#include <iostream>

/*
	The MIT License (MIT)

	Copyright (c) 2015, Ethan Riley <https://github.com/EthanRiley>
 	Copyright (c) contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

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
