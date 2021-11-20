#include"RegistrationController.h"
#include"ApplicationConfig.h"
#include"UserDetail.h"
#include"DbContext.h"

std::string RegistrationController::appUser(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail(arg));

	std::string data = "";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getConnectionString();

	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}

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
				data = result->find("table")->second;
		}
		std::free(result);
	}
	else {
		data.append("File: " + path + " not exists");
	}

	return "{\"menu\": " + data + "}";
}

std::string RegistrationController::Customer(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail(arg));
	userDetail->setPrivateFieldsValue(arg);

	std::string data = "";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getConnectionString();

	return "";
}
