#include"RegistrationController.h"
#include"ApplicationConfig.h"
#include"UserDetail.h"
#include"DbContext.h"
#include"Constants.h"

std::string RegistrationController::appUser(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(arg);

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
		query.append(userDetail->getUsername());
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
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(arg);

	std::list<std::string> params;
	params.push_back(Util::SqlStringValue(userDetail->getFirstName()));
	params.push_back(Util::SqlStringValue(userDetail->getLastName()));
	params.push_back(Util::SqlStringValue("true"));
	params.push_back(Util::SqlStringValue(userDetail->getMobile()));
	params.push_back(Util::SqlStringValue(userDetail->getAlternetMobileNo()));
	params.push_back(Util::SqlStringValue(userDetail->getShopPhoneNumber()));
	params.push_back(Util::SqlStringValue(userDetail->getEmail()));
	params.push_back(Util::SqlStringValue(userDetail->getShopName()));
	params.push_back(Util::SqlStringValue(userDetail->getAddress()));
	params.push_back(Util::SqlStringValue(userDetail->getLicenseNo()));
	params.push_back(Util::SqlStringValue(userDetail->getGSTNo()));
	params.push_back(Util::SqlStringValue(userDetail->getState()));
	params.push_back(Util::SqlStringValue(userDetail->getCity()));
	params.push_back(Util::SqlStringValue(std::to_string(userDetail->getPincode())));
	params.push_back(Util::SqlStringValue(""));
	params.push_back(Util::SqlStringValue(userDetail->getImagePath()));
	params.push_back(Util::SqlValue(0));
	params.push_back(Util::SqlStringValue("Date()"));
	params.push_back(Util::SqlStringValue(""));
	params.push_back(Util::SqlValue(1));
	params.push_back(Util::SqlValue(0));
	params.push_back(Util::SqlValue(userDetail->getIsClient()));

	std::string data = dbUtility->execute("InsertNewCustomer", params);
	return data;
}

std::string RegistrationController::GetCustomers(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(arg);

	std::string SerachString = "1=1";
	std::string data = dbUtility->execute("SelectCustomer", { SerachString });
	return data;
}