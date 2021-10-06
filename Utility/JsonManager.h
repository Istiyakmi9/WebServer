#pragma once

#include<iostream>
#include<list>
#include<map>

#ifdef JSONMANAGER_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif


class DECLSPEC JsonManager
{
public:
	std::string stringify(std::string key, std::string value);
	static std::unique_ptr<std::list<std::string>> splitter(std::string sourceString, std::string delimiter);
	static std::unique_ptr<std::list<std::string>> firstSplitter(std::string sourceString, std::string delimiter);
	
	static void ltrim(std::string& s);
	static void rtrim(std::string& s);
	static void trim(std::string& s);

	static std::map<std::string, std::string>* toRequestMap(std::string json);
};

