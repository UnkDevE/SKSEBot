#include "BaseAuRegClass.h"
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


std::vector<std::string> Regex_Search_Iterate(std::string input, boost::regex Regex) {
	
	std::string::const_iterator start = input.begin();
	std::string::const_iterator end = input.end();
	boost::smatch matches;
	std::vector<std::string> tmp;

	while (boost::regex_search(start, end, matches, Regex)) {
		tmp.push_back(std::string(matches[1].first, matches[1].second));
		
		start = matches[0].second;
	}
	return tmp;
}



bool AutoRegister::ReadClass(std::string HeaderFilename){
	HeaderFile.open(HeaderFilename,std::ios::in);
	
	std::string HeaderFileData;
	while (!HeaderFile.eof()) {
		HeaderFileData.push_back(HeaderFile.get());
	}

	boost::regex RegularExp(R"(([\w\n]+)(?=[{]))");
	boost::smatch Results;
	boost::regex_search(HeaderFileData, Results, RegularExp);
	RegData.classname = Results[1];
	std::cout << RegData.classname << std::endl;
	

	RegularExp.assign(R"(([\w\s\*\(),\n]+)(?=[)]))");
	std::vector<std::string> functionStrs=Regex_Search_Iterate(HeaderFileData, RegularExp);

	for (unsigned i = 0; i < functionStrs.size(); i++) {
		Function TempFunction;
		RegularExp.assign(R"((\w+)(?=[(]))");
		boost::regex_search(functionStrs[i], Results, RegularExp);
		TempFunction.functioname = Results[0];
		
		RegularExp.assign(R"(([\w\s\*]+)(?=[(]))");
		boost::regex_search(functionStrs[i], Results, RegularExp);
		std::string FunctionTillBrackets = Results[0].str();
		FunctionTillBrackets.resize(FunctionTillBrackets.size()-TempFunction.functioname.size());
		TempFunction.returntype = FunctionTillBrackets;

		RegularExp.assign(R"([\(,][\n\s]*([\w\*]+))");

		std::string::const_iterator start = functionStrs[i].begin();
		std::string::const_iterator end = functionStrs[i].end();
		boost::smatch matches;
		boost::regex rgx("StaticFunctionTag");

		for (unsigned b = 0; boost::regex_search(start, end, matches, RegularExp);  b++) {
			TempFunction.Argumentypes.push_back(std::string(matches[1].first, matches[1].second));
			TempFunction.staticFunction = boost::regex_search(TempFunction.Argumentypes[b], rgx);
			start = matches[0].second;
		}
		
		RegularExp.assign(R"(([\w\*]+)[\n\s]*[,)])");
		TempFunction.Arguments = Regex_Search_Iterate(functionStrs[i], RegularExp); // only used if using CreateClassSelfuntions
		
		RegData.Functions.push_back(TempFunction);
	}
	
	HeaderFile.close();
	return true;
}

bool AutoRegister::CreateClassSelfunctions(std::string newNamespaceFilename) {
	std::fstream N_OutputFile(newNamespaceFilename, std::ios::out|std::ios::trunc);
	N_OutputFile << "namespace " << RegData.classname << "{\n";

	for (unsigned i = 0; i < RegData.Functions.size(); i++) {
		N_OutputFile << '\t' <<RegData.Functions[i].returntype << RegData.Functions[i].functioname << "(";
		N_OutputFile << RegData.classname << "* self";
		if (RegData.Functions[i].Arguments.size() != 0) {
			N_OutputFile << RegData.Functions[i].Arguments[0];
		}

		for (unsigned b = 0; b < RegData.Functions[i].Arguments.size(); b++) {
			N_OutputFile << ",  " << RegData.Functions[i].Arguments[i];
		}

		N_OutputFile << ')';

		N_OutputFile << "{ \n\t\treturn" << " self";
		N_OutputFile << "->" << RegData.Functions[i].functioname << '(';
		
		for (unsigned b = 0; b < RegData.Functions[i].Arguments.size(); b++) {
			N_OutputFile << ",  " << RegData.Functions[i].Arguments[i];
		}

		N_OutputFile << ");\n\t}";
	}
	N_OutputFile << "\n}";
	N_OutputFile.close();
	return true;
}

bool AutoRegister::CreateFunctionCalls(std::string HeaderFilename) {
	ReadClass(HeaderFilename);
	
	OutputFile << R"(#include <PapyrusNativeFunctions.h>)";
	OutputFile << "\n\nbool RegisterFuncs(VMClassRegistry* registry) {\n";
	
	for (unsigned i = 0; i < RegData.Functions.size(); i++) {
		OutputFile << "\n\tregistry->RegisterFunction(\n";

		unsigned RegArgTySize = RegData.Functions[i].Argumentypes.size();

		OutputFile << "\t\tnew NativeFunction" << RegArgTySize << '<';
		
		if (!RegData.Functions[i].staticFunction) OutputFile << RegData.classname;
		else OutputFile << "StaticFunctionTag";

		OutputFile<< ", " << RegData.Functions[i].returntype;
	
		for (unsigned b = 0; b < RegArgTySize; b++) {
			OutputFile << ", " << RegData.Functions[i].Argumentypes[b];
		}

		OutputFile <<R"(>(")" <<RegData.Functions[i].functioname << R"(", ")"<< RegData.classname <<R"(", )";
		OutputFile << RegData.classname << "::" << RegData.Functions[i].functioname << ", registry));\n";
		
	}
	return true;
}

bool AutoRegister::CreateSetFunctionFlags(std::string functionflag) {
	for (unsigned i = 0; i < RegData.Functions.size(); i++) {
		OutputFile << "\n\t" << R"(registry->SetFunctionFlags(")" << RegData.classname << R"(", ")" << RegData.Functions[i].functioname << R"(", )";
		OutputFile << "VMClassRegistry::" << functionflag << ");";
	}
	OutputFile << '\n';
	return true;
}


