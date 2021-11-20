#pragma once

#include<iostream>

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
	static std::string toUpper(std::string);

	static std::string toLower(std::string);

	static std::string toCapitalize(std::string);

	static std::string combine(std::string, std::string);

	static std::string SqlStringValue(std::string);

	static std::string SqlValue(int);

	static std::string SqlValue(long);

	static std::string SqlCurrentDateTime();
};

