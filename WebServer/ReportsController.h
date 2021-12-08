#pragma once

#include<iostream>
#include"BaseController.h"
#include"DbUtility.h"
#include"JsonManager.h"

class ReportsController : public BaseController<ReportsController>
{
private:
	DbUtility* dbUtility;

public:
	ReportsController() {
		dbUtility = new DbUtility();

		add("GetCustomerById", bind(&ReportsController::GetCustomerById, this, _1));
	}

	~ReportsController() {
		delete dbUtility;
	}

	std::string GetCustomerById(std::string arg);
};
