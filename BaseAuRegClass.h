#pragma once
#include<vector>
#include<string>
#include<fstream>

using namespace std;
class AutoRegister {
public:
	//DO NOT SET The headerfile as the outputfile otherwise grief is innament(it will delete all your work)
	AutoRegister(bool IsNamespace,string HeaderFilename, string OutputFilename){
		HeaderFile.open(HeaderFilename,ios::in);
		OutputFile.open(OutputFilename,ios::out|ios::trunc);
		ReadClass(IsNamespace);
		if(!IsNamespace){
			CreateClassSelfFunctions();
			HeaderFile.close();
			HeaderFile.open(RegData.classname+"_Namespace.h", ios::in);
			ReadClass(true);
		}
		CreateFunctionCalls();
	}

	~AutoRegister() {
		HeaderFile.close();
		OutputFile.close();
	}
private:
	struct Function {
	public:
		vector<string> Argumentypes;
		string returntype;
		string functioname;
		vector<string> Arguments;
	};
	struct RegisterDataHold {
		public:
			vector<Function> Functions;
			string classname;
	};
	bool WriteArgs(int i){
		if (RegData.Functions[i].Arguments.size() != 0) {
			for (unsigned b = 0; b <= RegData.Functions[i].Arguments.size(); b++) {
				OutputFile << ",  " << RegData.Functions[i].Arguments[i];
			}
		}
		return true;
	}

	RegisterDataHold RegData;
	bool ReadClass(bool Isnamespace);
	bool CreateClassSelfFunctions();
	bool CreateFunctionCalls();
	fstream OutputFile;
	fstream HeaderFile;
	fstream CppFile;
	string TmpData;
};