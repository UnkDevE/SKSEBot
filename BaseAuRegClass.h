#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<boost\regex.hpp>
#include<iostream>


/*
	The MIT License (MIT)
	Copyright (c) 2015, Ethan Riley <https://github.com/EthanRiley>
	
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

class AutoRegister {
public:
	//Truncates outputfile be careful
	AutoRegister(std::string HeaderFilename, std::string OutputFilename){
		OutputFile.open(OutputFilename,std::ios::out|std::ios::trunc);
		CreateFunctionCalls(OutputFilename)
	}
	
	//Creates the functions
	bool CreateFunctionCalls(std::string HeaderFilename);
	
	//creates function flags default nowait(kFunctionFlag_NoWait), does not need VMClassRegistry:: in functionflag
	bool CreateSetFunctionFlags(std::string functionflag="kFunctionFlag_NoWait");

	//Used if you are using classes not namespaces 
	bool CreateClassSelfunctions(std::string newNamespaceFilename);

	~AutoRegister() {
		OutputFile << "\n\treturn true; \n}";
		OutputFile.close();
	}

private:
	bool ReadClass(std::string HeaderFilename);
	
	struct Function {
	public:
		std::vector<std::string> Argumentypes;
		bool staticFunction;
		std::string returntype;
		std::string functioname;
		std::vector<std::string> Arguments;
	};
	struct RegisterDataHold {
		public:
			std::vector<Function> Functions;
			std::string classname;
	};
	RegisterDataHold RegData;
	
	std::fstream OutputFile;
};
