#pragma once
#include "BaseController.h"

class RegistrationController : public BaseController<RegistrationController>
{
public:
	RegistrationController() {
		add("appUser", bind(&RegistrationController::appUser, this, _1));
	}

	std::string appUser(std::string);
};

