#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<boost\regex.hpp>
#include<iostream>

/*
	Please credit me if you are using my code 
	Im working under the GPL3 Licesnse
	search it up on google when you have the time 
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
	//Truncates outputfile be careful
	AutoRegister(std::string HeaderFilename, std::string OutputFilename){
		HeaderFile.open(HeaderFilename,std::ios::in);
		OutputFile.open(OutputFilename,std::ios::out|std::ios::trunc);
		ReadClass();
	}

	//Creates the functions
	bool CreateFunctionCalls();
	
	//creates function flags default nowait(kFunctionFlag_NoWait), does not need VMClassRegistry:: in functionflag
	bool CreateSetFunctionFlags(std::string functionflag="kFunctionFlag_NoWait");

	//Used if you are using classes not namespaces 
	bool CreateClassSelfunctions(std::string newNamespaceFilename);

	~AutoRegister() {
		OutputFile << "\n\treturn true; \n}";
		HeaderFile.close();
		OutputFile.close();
	}

private:
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
	bool ReadClass();

	std::fstream OutputFile;
	std::fstream HeaderFile;
	std::fstream CppFile;
	std::string TmpData;
};