#pragma once

#include<iostream>
#include<list>
#include"ApplicationConfig.h"
#include"DbContext.h"
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
		delete applicationConfig;
	}

	std::string getResult(std::string procName, std::list<std::string> args, std::string outputKeyName = "");
	std::string execute(std::string procName, std::list<std::string> args);
	bool IsDbExists();
};

