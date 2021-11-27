#pragma once

#ifdef JSONMANAGER_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<sstream>
#include<string>
#include<list>
#include<map>
#include<ctime>
#include<iomanip>
#include"Util.h"
#include<unordered_map>

//enum class Type { String, Int, Long, Double, StructTm, Char, CharPointer, ConstChar, ConstCharPointer };

class DECLSPEC JsonManager
{
public:
	JsonManager() { }

	std::string stringify(std::string key, std::string value);
	std::string stringify(std::map<std::string, std::string>* p);
	static std::unique_ptr<std::list<std::string>> splitter(std::string sourceString, std::string delimiter);
	static std::unique_ptr<std::list<std::string>> firstSplitter(std::string sourceString, std::string delimiter);

	static void ltrim(std::string& s);
	static void rtrim(std::string& s);
	static void trim(std::string& s);

	static std::map<std::string, std::string>* toRequestMap(const std::string json);

	static struct tm* ConvertToDateTime(const std::string& value);
	template<typename T>
	static T ConvertTo(std::string& value) {
		const char* type = typeid(T).name();
		std::string Type = type;
		if (Type.find("std::basic_string", 0) != -1) {
			return T(value.c_str());
		}
		T result = T();
		try {
			;
			std::istringstream ss(value);
			ss >> result;
		}
		catch (const std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}

		/*Type templateType = typemap.find(std::string(type))->second;
		switch (templateType) {
		case Type::String:
		{
			std::istringstream ss(value);
			ss >> result;
		}
		break;
		case Type::Long:
		{
			std::istringstream ss(value);
			ss >> result;
		}
		break;
		}*/

		return result;
	}
};

