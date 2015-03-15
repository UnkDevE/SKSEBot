#include "BaseAuRegClass.h"
#include<iostream>
using namespace std;


bool AutoRegister::ReadClass(bool Isnamespace){
	getline(HeaderFile, TmpData,'{'); 
	unsigned start = 0;
	if (Isnamespace) {
		start = TmpData.find("namespace ") + 10;
		RegData.classname = TmpData.substr(start, TmpData.size() - start);
		HeaderFile.seekg('{');
	}
	else {
		unsigned End = TmpData.find(':');
		if ( End == string::npos)End = TmpData.size();
		start = TmpData.find("class ") + 6;
		RegData.classname = TmpData.substr(start, End-start);
		RegData.classname.pop_back();
		HeaderFile.seekg(':');
	}
	bool breaker = false;
	for (int i = 0; !breaker; i++) {
		getline(HeaderFile, TmpData,'(');
		unsigned lastspace = TmpData.find_last_of(' ');
		unsigned lastTab = TmpData.find_last_of('\t', lastspace - 1);

		Function TempFunc;
		TempFunc.functioname = TmpData.substr(lastspace + 1, TmpData.size());
		TempFunc.returntype = TmpData.substr(lastTab + 1,lastspace-lastTab);
		

		if (TmpData != "") {
			
		
			unsigned FirstComma = 0;
			unsigned NextComma = 0;

			bool breakerArgs = false;
			getline(HeaderFile, TmpData, ')');
			for (int b = 0; !breakerArgs; b++) {

				FirstComma = TmpData.find(',', b);
				cout << FirstComma << endl;
				NextComma = TmpData.find(',', FirstComma + 1);

				if (NextComma != string::npos) {
					TempFunc.Arguments.push_back(TmpData.substr(FirstComma, NextComma));
					TempFunc.Argumentypes.push_back(TmpData.substr(0, TmpData.find(' ')));//copy beacuse of breaker :(
				}
				else if (FirstComma != string::npos) {
					TempFunc.Arguments.push_back(TmpData.substr(FirstComma, TmpData.size() - FirstComma));
					TempFunc.Argumentypes.push_back(TmpData.substr(0, TmpData.find(' ')));
				}
				else {
					lastspace = TmpData.find(' ') + 1;
					TempFunc.Arguments.push_back(TmpData.substr(lastspace,TmpData.size()-lastspace));
					TempFunc.Argumentypes.push_back(TmpData.substr(0, TmpData.find(' ')));
					breakerArgs = true;
				}
				
				}
			}
		streamoff Filepos = HeaderFile.tellg();
		RegData.Functions.push_back(TempFunc);
		getline(HeaderFile, TmpData, '\n');
		cout << TmpData << endl;
		if (TmpData.find("END") != string::npos)breaker = true;
		else HeaderFile.seekg(Filepos);
	}
	return true;
}

bool AutoRegister::CreateClassSelfFunctions() {
	fstream N_OutputFile(RegData.classname + "_Namespace" + ".h",ios::out|ios::trunc);
	N_OutputFile << "namespace " << RegData.classname << "_Namespace" << "{\n";

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

		unsigned RegArgSize = RegData.Functions[i].Arguments.size();
		OutputFile << "\tnew NativeFunction" << RegArgSize << '<' << RegData.classname << ", " << RegData.Functions[i].returntype;

		for (unsigned b = 0; b < RegArgSize; b++) {
			OutputFile << ", " << RegData.Functions[i].Argumentypes[b];
		}
		OutputFile << '>';

		OutputFile << '(' << '"' << RegData.Functions[i].functioname << '"' << ", " << '"' << RegData.classname << '"' << ", ";
		OutputFile << RegData.classname << "::" << RegData.Functions[i].functioname << ", " << "registry));";
	}
	OutputFile << "\n\treturn true; \n}";
	return true;
}


