#include"ItemAndGoodsController.h"
#include<list>
#include"Util.h"
#include"JsonManager.h"
#include"ApplicationConfig.h"

std::string ItemAndGoodsController::GetStocks(std::string args) {
	std::string searchString = " 1=1 ";
	std::map<std::string, std::string>* result = new std::map<std::string, std::string>();
	/*------------  Select Stocks detail data -------------------------*/
	std::unique_ptr<std::map<std::string, std::string>> request(JsonManager::toRequestMap(args));
	if (request->count("SearchString") > 0)
		searchString = request->find("SearchString")->second;
	result->insert({ "rows", dbUtility->getResult("SelectStocks", { searchString }) });
	result->insert({ "total", dbUtility->getResult("SelectStocksCount", { searchString }) });
	result->insert({ "columns", dbUtility->getResult("GetColumns", { "Stocks" }) });
	result->insert({ "customers", dbUtility->getResult("SelectCustomer", { "1=1" }) });
	JsonManager* manager = new JsonManager();
	auto response = manager->stringify(result);
	delete manager;
	delete result;
	return response;
}

std::string ItemAndGoodsController::GetStocksToAddNew(std::string args) {
	std::string searchString = " 1=1 ";
	std::map<std::string, std::string>* result = new std::map<std::string, std::string>();
	/*------------  Select Stocks detail data -------------------------*/
	std::unique_ptr<std::map<std::string, std::string>> request(JsonManager::toRequestMap(args));
	if (request->count("SearchString") > 0)
		searchString = request->find("SearchString")->second;
	result->insert({ "rows", dbUtility->getResult("SelectStocks", { searchString }) });
	result->insert({ "total", dbUtility->getResult("SelectStocksCount", { searchString }) });
	result->insert({ "columns", dbUtility->getResult("GetColumns", { "Stocks" }) });
	result->insert({ "customers", dbUtility->getResult("SelectCustomer", { " 1=1 AND IsClient = 0" }) });
	JsonManager* manager = new JsonManager();
	auto response = manager->stringify(result);
	delete manager;
	delete result;
	return response;
}

std::string ItemAndGoodsController::AddEditStockItem(std::string args) {
	ProductModal* productModal = new ProductModal();
	productModal->setPrivateFieldsValue(args);

	long brandUid = 0;
	if (productModal->getBrandUid() == 0)
		brandUid = checkBrandNameExists(productModal->getBranName());
	else
		brandUid = productModal->getBrandUid();

	bool isNewBrandCreated = false;
	std::list<std::string> param;
	if (brandUid == 0) {
		param.push_back(Util::SqlStringValue(productModal->getBranName()));
		param.push_back(Util::SqlStringValue(productModal->getDescription()));
		param.push_back(Util::SqlValue(productModal->getCatagoryUid()));
		param.push_back("Date()");
		param.push_back(Util::SqlStringValue(""));
		param.push_back(Util::SqlValue(productModal->getAdminId()));
		param.push_back(Util::SqlValue(0));
		dbUtility->execute("InsertNewBrand", param);
		isNewBrandCreated = true;

		brandUid = dbUtility->lastInsertId("ItemBrands");
	}

	std::string responseMessage = "";
	stockItem stock = getExistsRecord(productModal->getItemName());

	//---------------- for new item -------------------------
	if (stock.availableQuantity == 0) {
		stock.availableQuantity = productModal->getQuantity();
		responseMessage = insertNewStockItem(productModal, stock);
	}
	else { //------------------- for existing item ------------------
		stock.availableQuantity = stock.availableQuantity + productModal->getQuantity();
		responseMessage = updateStockItem(productModal, stock);
	}

	delete productModal;
	if (isNewBrandCreated)
		responseMessage = dbUtility->getResult("SelectItemBrands", {});
	return responseMessage;
}

stockItem ItemAndGoodsController::getExistsRecord(std::string name) {
	stockItem stock;
	std::string result = dbUtility->getResult("SelectStockByName", { name });
	std::map<std::string, std::string>* data = JsonManager::toRequestMap(result);
	if (data->count("Quantity") > 0) {
		stock.availableQuantity = stoi(data->find("Quantity")->second);
		stock.stockUid = stol(data->find("StockUid")->second);
	}
	else {
		stock.availableQuantity = 0;
		stock.stockUid = 0;
	}
	return stock;
}

std::string ItemAndGoodsController::insertNewStockItem(ProductModal* productModal, stockItem stock) {
	std::list<std::string> param;
	param.push_back(Util::SqlStringValue(""));
	param.push_back(Util::SqlStringValue(productModal->getItemName()));
	param.push_back(Util::SqlValue(productModal->getBrandUid()));
	param.push_back(Util::SqlStringValue(productModal->getSerialNo()));
	param.push_back(Util::SqlValue(productModal->getCatagoryUid()));
	param.push_back(Util::SqlValue(productModal->getQuantity()));
	param.push_back(Util::SqlValue(stock.availableQuantity));
	param.push_back(Util::SqlValue(productModal->getActualPrice()));
	param.push_back(Util::SqlValue(productModal->getSellingPrice()));
	param.push_back(Util::SqlValue(productModal->getMRP()));
	param.push_back(Util::SqlValue(0));
	param.push_back(Util::SqlStringValue(""));
	param.push_back(Util::SqlCurrentDateTime());
	param.push_back(Util::SqlStringValue(""));
	param.push_back(Util::SqlValue(productModal->getAdminId()));
	param.push_back(Util::SqlValue(0));
	param.push_back(Util::SqlValue(0));

	std::string result = dbUtility->execute("InsertNewStock", param);
	if (result != "Fail")
		result = "Record inserted successfully";
	return result;
}

std::string ItemAndGoodsController::updateStockItem(ProductModal* productModal, stockItem stock) {
	std::list<std::string> param;
	param.push_back(Util::SqlValue(productModal->getBrandUid()));
	param.push_back(Util::SqlStringValue(productModal->getSerialNo()));
	param.push_back(Util::SqlValue(productModal->getCatagoryUid()));
	param.push_back(Util::SqlValue(productModal->getQuantity()));
	param.push_back(Util::SqlValue(stock.availableQuantity));
	param.push_back(Util::SqlValue(productModal->getActualPrice()));
	param.push_back(Util::SqlValue(productModal->getSellingPrice()));
	param.push_back(Util::SqlValue(productModal->getMRP()));
	param.push_back(Util::SqlValue(0));
	param.push_back(Util::SqlStringValue(""));
	param.push_back(Util::SqlCurrentDateTime());
	param.push_back(Util::SqlValue(productModal->getAdminId()));
	param.push_back(Util::SqlValue(0));
	param.push_back(Util::SqlValue(stock.stockUid));

	std::string result = dbUtility->execute("UpdateStock", param);
	if (result != "Fail")
		result = "Record updated successfully";
	return result;
}

long ItemAndGoodsController::checkBrandNameExists(std::string name) {
	long brandUid = 0;
	std::string result = dbUtility->getResult("BrandNameExists", { name });
	std::map<std::string, std::string>* data = JsonManager::toRequestMap(result);
	if (data->size() > 0 && data->count("BrandUid") > 0)
		brandUid = stol(data->find("BrandUid")->second);
	delete data;
	return brandUid;
}

std::string ItemAndGoodsController::GetProductByFilter(std::string args) {
	std::string result = "";
	std::map<std::string, std::string>* request = JsonManager::toRequestMap(args);
	if (request->count("SearchString") > 0) {
		result = dbUtility->getResult("SelectStocks", { request->find("SearchString")->second });
	}
	return result;
}