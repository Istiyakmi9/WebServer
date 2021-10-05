#pragma once

#include<iostream>
#include<map>
#include<functional>
#include"BaseController.h"

using std::placeholders::_1;

class LoginController : public BaseController<LoginController>
{
public:
	//typedef std::function<std::string(LoginController&)> fnptr;
	//fnptr func;
	//std::map<std::string, fnptr>* fn;
	LoginController() {

		/*fn = new std::map<std::string, fnptr>();

		fn->insert({ "Auth", std::bind(&LoginController::Auth, _1) });
		fn->insert({ "Registration", std::bind(&LoginController::Auth, _1) });*/


		add("auth", std::bind(&LoginController::Auth, this, _1));
	}

	~LoginController(){ }

	std::string Auth(std::string);
};

