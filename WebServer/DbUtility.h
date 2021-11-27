#pragma once

#include<iostream>
#include<list>
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"Constants.h"
#include<map>

class DbUtility
{
private:
	DbContext* context = nullptr;
	std::map<std::string, std::string>* result = nullptr;
	ApplicationConfig* applicationConfig = nullptr;
	std::string path;

public:
	DbUtility() {
		applicationConfig = ApplicationConfig::getInstance();
		path = applicationConfig->getConnectionString();
		context = new DbContext(path.c_str());
	}

	~DbUtility() {
		delete context;
		applicationConfig = nullptr;
		delete result;
	}

	std::string getResult(std::string procName, std::list<std::string> args, std::string outputKeyName = "");
	std::map<std::string, std::string>* getResultMap(std::string procName, std::list<std::string> args);
	std::string execute(std::string procName, std::list<std::string> args);
	std::string execute(std::string procName, std::map<std::string, Constants::DataType> args);
	int lastInsertId(std::string Table);
	bool IsDbExists();
};

