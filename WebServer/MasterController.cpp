#include "MasterController.h"
#include"sqlite3.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"UserDetail.h"
#include<stdio.h>
#include<JsonManager.h>
#include<map>
#include"ProductModal.h"
#include"Constants.h"

std::string MasterController::PageMasterData(std::string args) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail(args));
	return "";
}

std::string MasterController::AddOrUpdateCatagory(std::string args) {
	/*std::unique_ptr<ProductModal> productModal(new ProductModal(args));

	std::string data = "Invalid data";
	if (productModal->getCatagoryName() != "") {
		data = dbUtility->getResult("InsertCatagory", {
				"0",
				"'" + productModal->getCatagoryName() + "'",
				"'" + productModal->getDescription() + "'",
				"Date()",
				"''",
				"1",
				"0"
			});
	}*/

	return ""; // data;
}