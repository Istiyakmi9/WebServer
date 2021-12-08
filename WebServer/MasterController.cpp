#include"MasterController.h"
#include"ProductModal.h"
#include"UserDetail.h"

std::string MasterController::PageMasterData(std::string args) {
	std::unique_ptr<UserDetail> userDetail(new UserDetail());
	userDetail->setPrivateFieldsValue(args);
	return "";
}

std::string MasterController::AddOrUpdateCatagory(std::string args) {
	std::unique_ptr<ProductModal> productModal(new ProductModal());
	productModal->setPrivateFieldsValue(args);

	std::string data = "Invalid data";
	if (productModal->getCatagoryName() != "") {
		data = dbUtility->execute("InsertCatagory", {
				"0",
				"'" + productModal->getCatagoryName() + "'",
				"'" + productModal->getDescription() + "'",
				"Date()",
				"''",
				std::to_string(productModal->getCGST()),
				std::to_string(productModal->getSGST()),
				std::to_string(productModal->getIGST()),
				"1",
				"0"
			});
	}

	return data;
}