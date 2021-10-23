#pragma once

#include"BaseController.h"
#include<iostream>
#include<functional>


class ItemAndGoodsController : public BaseController<ItemAndGoodsController>
{
public:
	ItemAndGoodsController() {
		add("AddEditStockItem", bind(&ItemAndGoodsController::AddEditStockItem, this, _1));
	}

	std::string AddEditStockItem(std::string);
};

