#pragma once

#include<iostream>
#include<list>
#include<map>
#include <functional>

#ifndef UTIL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // !UTIL_H

#include<map>
enum class Type { String, Int, Long, Double, StructTm, Char, CharPointer, ConstChar, ConstCharPointer };

class DECLSPEC Util
{
public:
	static std::unique_ptr<std::list<std::string>> splitter(std::string sourceString, std::string delimiter);

	static std::unique_ptr<std::list<std::string>> singleSplitter(std::string sourceString, std::string delimiter);

	static std::map<std::string, std::string>* jsonToMap(std::string sourceString);

	static std::string toUpper(std::string);

	static std::string toLower(std::string);

	static std::string toCapitalize(std::string);

	static std::string combine(std::string, std::string);

	static std::string SqlStringValue(std::string);

	static std::string SqlValue(int);

	static std::string SqlValue(long);

	static std::string SqlCurrentDateTime();

	static void ltrim(std::string& s);

	static void rtrim(std::string& s);

	static void trim(std::string& s);

	static std::string replace_all(std::string, std::string, std::string);
};

