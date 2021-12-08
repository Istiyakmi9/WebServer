#include "DashboardController.h"
#include"UserDetail.h"

std::string DashboardController::getMenu(std::string args) {
	UserDetail* userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(args);

	std::string data = "";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getConnectionString();

	DbContext* context = new DbContext(path.c_str());
	std::string query = "Select * from menu'";
	query.append(userDetail->getUsername());
	query.append("' and Password = '");
	query.append(userDetail->getPassword());
	query.append("';");

	std::map<std::string, std::string>* result = context->getResultSet(query.c_str());
	if (result->count("table") > 0)
		data = result->find("table")->second;
	std::free(result);

	delete userDetail;
	delete context;
	delete applicationConfig;
	return data;
}