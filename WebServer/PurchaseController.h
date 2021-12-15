#pragma once

#include<iostream>
#include"BaseController.h"

class PurchasedController : public BaseController<PurchasedController>
{
public:
	explicit PurchasedController() {
		add("addPurchedItems", bind(&PurchasedController::addPurchedItems, this, _1));
	}

	std::string addPurchedItems(std::string param);
};

