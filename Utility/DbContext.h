#pragma once

#ifndef DBCONTEXT_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // !DBCONTEXT_H

#include<iostream>
#include<map>

class DECLSPEC DbContext
{
private:
	const char* path;
	std::map<std::string, std::string>* resultSet = nullptr;

public:
	DbContext(const char* dbPath) {
		path = dbPath;
		resultSet = new std::map<std::string, std::string>();
	}
	int executeNonQuery(const char* query);
	std::map<std::string, std::string>* getResultSet(const char* query);
	void setResult(std::string key, std::string value);
};

