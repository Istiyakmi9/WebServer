#pragma once

#include"BaseController.h"
#include<iostream>
#include<functional>
#include"DbUtility.h"
#include"ProductModal.h"

typedef struct {
	int availableQuantity;
	long stockUid;
}stockItem;

class ItemAndGoodsController : public BaseController<ItemAndGoodsController>
{
private:
	DbUtility* dbUtility;
public:
	ItemAndGoodsController() {
		dbUtility = new DbUtility();

		add("AddEditStockItem", bind(&ItemAndGoodsController::AddEditStockItem, this, _1));
		add("GetStocks", bind(&ItemAndGoodsController::GetStocks, this, _1));
		add("GetProductByFilter", bind(&ItemAndGoodsController::GetProductByFilter, this, _1));
		add("GetStocksToAddNew", bind(&ItemAndGoodsController::GetStocksToAddNew, this, _1));
	}

	~ItemAndGoodsController() {
		delete dbUtility;
	}

	std::string AddEditStockItem(std::string);
	long checkBrandNameExists(std::string);
	std::string insertNewStockItem(ProductModal*, stockItem);
	std::string updateStockItem(ProductModal*, stockItem);
	stockItem getExistsRecord(std::string);
	std::string GetStocks(std::string);
	std::string GetProductByFilter(std::string);
	std::string GetStocksToAddNew(std::string args);
};

