#include"LoginController.h"
#include"sqlite3.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"UserDetail.h"
#include<stdio.h>
#include<JsonManager.h>
#include<map>

std::string LoginController::Auth(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail(arg));

	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getConnectionString();

	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}

	std::stringstream data;
	data << "{";
	if (fileExists) {
		DbContext* context = new DbContext(path.c_str());
		
		std::string query = "Select * from login where Username='";
		query.append(userDetail->getUserName());
		query.append("' and Password = '");
		query.append(userDetail->getPassword());
		query.append("';");

		std::map<std::string, std::string>* result = context->getResultSet(query.c_str());
		if (result->count("table") > 0) {
			std::free(result);

			query = "SELECT * from rolesandmenu;";
			result = context->getResultSet(query.c_str());

			if (result->count("table") > 0)
				data << "\"menu\": " + result->find("table")->second;

			query = "SELECT * from Catagory;";
			result = context->getResultSet(query.c_str());

			if (result->count("table") > 0)
				data << ", \"catagory\": " + result->find("table")->second;

			query = "SELECT * from ItemBrands;";
			result = context->getResultSet(query.c_str());

			if (result->count("table") > 0)
				data << ", \"brands\": " + result->find("table")->second;
		}
		std::free(result);
	}
	else {
		data << "File: " + path + " not exists";
	}

	data << "}";
	return data.str();
}