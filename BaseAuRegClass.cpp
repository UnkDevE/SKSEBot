#include "BaseAuRegClass.h"
/*
	All right reseved, Ethan Riley.
	:)
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
bool AutoRegister::ReadClass(bool isClass){
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

		RegularExp.assign(R"(([\w\*]+)(?=[,)]))");
		TempFunction.Argumentypes = Regex_Search_Iterate(functionStrs[i], RegularExp);

		if (isClass) {
			RegularExp.assign(R"(([\w\*]+)(?=[,)]))");
			TempFunction.Arguments = Regex_Search_Iterate(functionStrs[i], RegularExp);
		}
		
		RegData.Functions.push_back(TempFunction);
	}

	return true;
}
bool AutoRegister::WriteArgs(int i) {
	if (RegData.Functions[i].Arguments.size() != 0) {
		for (unsigned b = 0; b < RegData.Functions[i].Arguments.size(); b++) {
			OutputFile << ",  " << RegData.Functions[i].Arguments[i];
		}
	}
	return true;
}
bool AutoRegister::CreateClassSelfFunctions(std::string newNamespaceFilename) {//currently not working
	std::fstream N_OutputFile(newNamespaceFilename + ".h",std::ios::out|std::ios::trunc);
	N_OutputFile << "namespace " << RegData.classname << "{\n";

	for (unsigned i = 0; i < RegData.Functions.size(); i++) {
		N_OutputFile << '\t' <<RegData.Functions[i].returntype << RegData.Functions[i].functioname << "(";
		N_OutputFile << RegData.classname << "* self";
		if (RegData.Functions[i].Arguments.size() != 0) {
			OutputFile << RegData.Functions[i].Arguments[0];
		}
		WriteArgs(i);
		N_OutputFile << ')';

		N_OutputFile << "{ \n\t\treturn" << " self";
		N_OutputFile << "->" << RegData.Functions[i].functioname << '(';
		WriteArgs(i);
		N_OutputFile << ");\n\t}";
	}
	N_OutputFile << "\\END \n}";
	return true;
}

bool AutoRegister::CreateFunctionCalls() {
	OutputFile << "bool RegisterFuncs(VMClassRegistry* registry) {";
	
	for (unsigned i = 0; i < RegData.Functions.size(); i++) {
		OutputFile << '\n' << "\tregistry->RegisterFunction(" << '\n';

		unsigned RegArgTySize = RegData.Functions[i].Argumentypes.size();
		OutputFile << "\t\tnew NativeFunction" << RegArgTySize << '<' << RegData.classname << ", " << RegData.Functions[i].returntype ;
	
		for (unsigned b = 0; b < RegArgTySize; b++) {
			OutputFile << ", " << RegData.Functions[i].Argumentypes[b];
		}
		OutputFile << '>';

		OutputFile << '(' << '"' << RegData.Functions[i].functioname << '"' << ", " << '"' << RegData.classname << '"' << ", ";
		OutputFile << RegData.classname << "::" << RegData.Functions[i].functioname << ", " << "registry));\n";
	}
	OutputFile << "\n\treturn true; \n}";
	return true;
}


