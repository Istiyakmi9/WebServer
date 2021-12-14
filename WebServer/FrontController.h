#pragma once

#include"HttpContext.h"
#include"HttpContext.h"
#include"DashboardController.h"
#include"ReportsController.h"
#include"ItemAndGoodsController.h"
#include"RegistrationController.h"
#include"MasterController.h"
#include"LoginController.h"
#include"BillingController.h"

enum class ControllerMapping {
	Login = 1,
	Reports = 2,
	Dashboard = 3,
	Registration = 4,
	Master = 5,
	ItemAndGoods = 6,
	Billing
};

class FrontController
{
private:
	std::map<std::string, ControllerMapping>* mapping;
	static FrontController* instance;
	FrontController() {
		mapping = new std::map<std::string, ControllerMapping>();
		mapping->insert({ "login", ControllerMapping::Login });
		mapping->insert({ "dashboard", ControllerMapping::Dashboard });
		mapping->insert({ "registration", ControllerMapping::Registration });
		mapping->insert({ "master", ControllerMapping::Master });
		mapping->insert({ "itemandgoods", ControllerMapping::ItemAndGoods });
		mapping->insert({ "reports", ControllerMapping::Reports });
		mapping->insert({ "billing", ControllerMapping::Billing });
	}

public:
	// -------------  Singleton ApplicationCofig: Stopping copy constructor ----------- //
	FrontController(const FrontController&) = delete;

	~FrontController() {
		delete instance;
		delete mapping;
	}

	// -------------  Singleton ApplicationCofig object should not be assignabled ----------- //
	void operator=(const FrontController&) = delete;

	/*
		Static method to get only one instance of
		the object with thread safe approach
	*/
	static FrontController* InstanceOf();

	std::string CallToController(HttpContext*);
};

