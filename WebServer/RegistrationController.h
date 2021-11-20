#pragma once
#include "BaseController.h"

class RegistrationController : public BaseController<RegistrationController>
{
public:
	RegistrationController() {
		add("appUser", bind(&RegistrationController::appUser, this, _1));
		add("Customer", bind(&RegistrationController::Customer, this, _1));
	}

	std::string appUser(std::string);
	std::string Customer(std::string);
};

