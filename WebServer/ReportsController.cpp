#include "ReportsController.h"

std::string ReportsController::GetCustomerById(std::string arg) {
	std::string data = "";
	std::map<std::string, std::string>* mapData = JsonManager::toRequestMap(arg);
	std::string procedureName = "InsertNewCustomer";
	std::string strUserId = mapData->find("UserUid")->second;
	if (strUserId != "") {
		std::map<std::string, std::string>* resultSet = new std::map<std::string, std::string>();
		int userId = atoi(strUserId.c_str());
		JsonManager* jsonManager = new JsonManager();
		resultSet->insert({ "CustomerDetail", dbUtility->getResult("CustomerExistsById", {Util::SqlValue(userId)}) });
		resultSet->insert({ "Files", dbUtility->getResult("GetFilesByOwnerId", {Util::SqlValue(userId)}) });
		data = jsonManager->stringify(resultSet);
		delete jsonManager;
		delete resultSet;
	}
	return data;
}