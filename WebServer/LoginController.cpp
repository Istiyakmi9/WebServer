#include "LoginController.h"
#include"sqlite3.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"UserDetail.h"
#include<stdio.h>

std::string LoginController::Auth(std::string arg) {
	std::string data = "";
	std::string databaseName = "anyshop.db";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getApplicationWorkingDirectory() + "\\" + databaseName;
	std::cout << "Database path:" << path << std::endl;

	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}

	if (fileExists) {
		DbContext* context = new DbContext(path.c_str());
		std::map<std::string, std::string>* result = context->getResultSet("Select * from login;");
		data = result->find("table")->second;
		std::free(result);
	}
	else {
		data.append("File: " + databaseName + " not exists");
	}

	return data;
}