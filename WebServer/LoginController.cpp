#include"LoginController.h"
#include"sqlite3.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"UserDetail.h"
#include<stdio.h>
#include<JsonManager.h>
#include<map>
#include"JsonManager.h"

std::string LoginController::Auth(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(arg);

	std::string data;
	std::unique_ptr<std::map<std::string, std::string>> resultSet = nullptr;

	std::string Result = dbUtility->getResult("SelectLogin", {
			userDetail->getUsername(),
			userDetail->getPassword()
		});

	if (Result != "") {
		resultSet = std::make_unique<std::map<std::string, std::string>>();

		/*------------  Select RolesAndMenu data -------------------------*/
		resultSet->insert({ "menu", dbUtility->getResult("SelectRolesAndMenu", {}) });

		/*------------  Select Catagory detail data -------------------------*/
		resultSet->insert({ "catagory", dbUtility->getResult("SelectCatagory", { "1=1" })});

		/*------------  Select Brands detail data -------------------------*/
		resultSet->insert({ "brands", dbUtility->getResult("SelectItemBrands", {}) });

		std::unique_ptr<JsonManager> jsonManager(new JsonManager());
		data = jsonManager->stringify(resultSet.get());
	}
	return data;
}