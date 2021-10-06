#pragma once

#include<iostream>
#include<map>
#include<functional>
#include"BaseController.h"

using std::placeholders::_1;

class LoginController : public BaseController<LoginController>
{
public:
	LoginController() {
		add("auth", bind(&LoginController::Auth, this, _1));
	}

	~LoginController(){ }

	std::string Auth(std::string);
};

