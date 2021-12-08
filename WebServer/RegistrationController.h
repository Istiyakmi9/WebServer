#pragma once
#include"BaseController.h"
#include"DbUtility.h"
#include"FileDetail.h"
#include"UserDetail.h"
#include"ApplicationConfig.h"
#include"DbContext.h"
#include"Constants.h"
#include"FileManager.h"

class RegistrationController : public BaseController<RegistrationController>
{
private:
	DbUtility* dbUtility;

public:
	RegistrationController() {
		dbUtility = new DbUtility();


		add("appUser", bind(&RegistrationController::appUser, this, _1));
		add("Customer", bind(&RegistrationController::Customer, this, _1));
		add("GetCustomers", bind(&RegistrationController::GetCustomers, this, _1));
	}

	~RegistrationController() {
		delete dbUtility;
	}

	std::string appUser(std::string);
	std::string Customer(std::string);
	std::string GetCustomers(std::string arg);
};

