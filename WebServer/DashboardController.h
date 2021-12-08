#pragma once

#include<iostream>
#include"BaseController.h"
#include<JsonManager.h>
#include<ApplicationConfig.h>
#include<DbContext.h>

class DashboardController : public BaseController<DashboardController>
{
public:
	DashboardController() {
		add("auth", bind(&DashboardController::getMenu, this, _1));
	}

	std::string getMenu(std::string);
};

