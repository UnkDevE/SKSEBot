#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<boost\regex.hpp>
#include<iostream>

/*
	Please Credit me if you are using my code 
	Im working under the GPL3 Licesnse
	seacrch it up on google when you have the time 
	if you need this in capital letters for it to be more 'licencey'
	Here you go:
		PLEASE CERDIT ME IF YOU ARE USING MY CODE
		IM WORKING UNDER THE GPL3 LICENCSE
		SEARCH IT UP ON GOOGLE WHEN YOU HAVE THE TIME
	All right reseved, Ethan Riley.
	:)
*/


class AutoRegister {
public:
	//Do not set yhe headerfile as the outputfile otherwise it will delete your work! don't do newlines before () in headerfile
	AutoRegister(std::string HeaderFilename, std::string OutputFilename){
		HeaderFile.open(HeaderFilename,std::ios::in);
		OutputFile.open(OutputFilename,std::ios::out|std::ios::trunc);
		ReadClass(false);
		CreateFunctionCalls();
	}
	AutoRegister(std::string HeaderFilename, std::string OutputFilename,std::string NewNamspaceFilename) {
		HeaderFile.open(HeaderFilename, std::ios::in);
		OutputFile.open(OutputFilename, std::ios::out | std::ios::trunc);
		ReadClass(true);
		CreateFunctionCalls();
		CreateClassSelfFunctions(NewNamspaceFilename);
	}
	bool CreateClassSelfFunctions(std::string newNamespaceFilename);
	~AutoRegister() {
		HeaderFile.close();
		OutputFile.close();
	}
private:
	struct Function {
	public:
		std::vector<std::string> Argumentypes;
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
	bool WriteArgs(int i);
	bool ReadClass(bool isClass);
	bool CreateFunctionCalls();
	std::fstream OutputFile;
	std::fstream HeaderFile;
	std::fstream CppFile;
	std::string TmpData;
};