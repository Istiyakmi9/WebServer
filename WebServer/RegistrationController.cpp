#include"RegistrationController.h"

std::string RegistrationController::appUser(std::string arg) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(arg);

	std::string data = "";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getConnectionString();

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

	return "{\"menu\": " + data + "}";
}

std::string RegistrationController::Customer(std::string arg) {
	std::string data = "";
	arg = this->httpRequest->getFormJsonData("userDetail");
	if (arg != "") {
		std::unique_ptr<UserDetail> userDetail(new UserDetail());
		userDetail->setPrivateFieldsValue(arg);
		bool isUpdate = false;
		std::string procedureName = "InsertNewCustomer";
		int userId = userDetail->getUserUid();
		if (userId > 0) {
			data = dbUtility->getResult("CustomerExistsById", { Util::SqlValue(userId) });
			if (data != "") {
				procedureName = "UpdateCustomer";
				isUpdate = true;
			}
		}

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
		if (!isUpdate) {
			params.push_back("Date()");
			params.push_back(Util::SqlStringValue(""));
			params.push_back(Util::SqlValue(1));
			params.push_back(Util::SqlValue(0));
			params.push_back(Util::SqlValue(userDetail->getIsClient()));
		}
		else {
			params.push_back("Date()");
			params.push_back(Util::SqlValue(1));
			params.push_back(Util::SqlValue(userId));
		}

		data = dbUtility->execute(procedureName, params);
		if (data != "") {
			long customerUid = userId;
			if (!isUpdate) {
				data = dbUtility->getResult("GetLastSequenceKey", { Util::SqlStringValue("Customer") });
				auto result = Util::jsonToMap(data);
				customerUid = atol(result->find("seq")->second.c_str());
			}
			FileDetail* fileDetail = new FileDetail();
			fileDetail->setFileDetailId(userDetail->getExistingFileDetailId());
			fileDetail->setFileOwnerId(userDetail->getUserUid());
			fileDetail->setFilePath("UploadedFiles");
			FileManager* fileManager = new FileManager();
			data = fileManager->saveFile("image", fileDetail, httpRequest);
			delete fileDetail;
			delete fileManager;
		}
		else {
			data = "Fail to create. Please contact to admin.";
		}
	}
	return data;
}

std::string RegistrationController::GetCustomers(std::string arg) {
	std::string searchString = " 1=1 ";
	std::map<std::string, std::string>* result = new std::map<std::string, std::string>();
	/*------------  Select Stocks detail data -------------------------*/
	std::unique_ptr<std::map<std::string, std::string>> request(JsonManager::toRequestMap(arg));
	if (request->count("SearchString") > 0)
		searchString = request->find("SearchString")->second;
	result->insert({ "rows", dbUtility->getResult("SelectCustomer", { searchString }) });
	result->insert({ "total", dbUtility->getResult("SelectCustomerCount", { searchString }) });
	result->insert({ "columns", dbUtility->getResult("GetColumns", { "Customer" }) });
	JsonManager* manager = new JsonManager();
	auto response = manager->stringify(result);
	delete manager;
	delete result;
	return response;
}