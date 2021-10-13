#include "MasterController.h"
#include"sqlite3.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"UserDetail.h"
#include<stdio.h>
#include<JsonManager.h>
#include<map>
#include"ProductModal.h"

std::string MasterController::PageMasterData(std::string args) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail(args));

	std::string data = "";
	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}

	if (fileExists) {
		//DbContext* context = new DbContext(path.c_str());

		//std::string query = "Select * from login where Username='";
		//query.append(userDetail->getUserName());
		//query.append("' and Password = '");
		//query.append(userDetail->getPassword());
		//query.append("';");

		//std::map<std::string, std::string>* result = context->getResultSet(query.c_str());
		//if (result->count("table") > 0) {
		//}
		//std::free(result);
	}
	else {
		data.append("File: " + path + " not exists");
	}

	return "";
}

std::string MasterController::AddOrUpdateCatagory(std::string args) {
	std::unique_ptr<ProductModal> productModal(new ProductModal(args));

	std::string data = "";
	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}

	if (fileExists && productModal->getCatagoryName() != "") {
		DbContext* context = new DbContext(path.c_str());

		std::string query = "Insert into Catagory(ParentCatagoryUid, CatagoryName, Description, AddedOn, UpdateOn, CreatedBy, ModifiedBy) Values(";
		query.append("0,");
		query.append("'" + productModal->getCatagoryName() + "',");
		query.append("'" + productModal->getDescription() + "',");
		query.append("Date(),");
		query.append("'',");
		query.append("1,");
		query.append("0");
		query.append(");");

		int count = context->executeNonQuery(query.c_str());
		delete context;
		if (count == 0)
			return "Insert Or update successfull.";
	}
	else {
		data.append("File: " + path + " not exists");
	}

	return "";
}