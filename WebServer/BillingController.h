#pragma once

#include<iostream>
#include"BaseController.h"

class BillingController : public BaseController<BillingController>
{
public:
	explicit BillingController() {
		add("addBillingData", bind(&BillingController::addBillingData, this, _1));

	}
	
	std::string addBillingData(std::string param);
};

