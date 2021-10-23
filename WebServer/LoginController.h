#pragma once

#include<iostream>
#include<map>
#include<functional>
#include"BaseController.h"
#include"DbUtility.h"

class LoginController : public BaseController<LoginController>
{
private:
	DbUtility* dbUtility = nullptr;
	
public:
	LoginController() {
		dbUtility = new DbUtility();

		add("auth", bind(&LoginController::Auth, this, _1));
	}

	~LoginController(){ }

	std::string Auth(std::string);
};

