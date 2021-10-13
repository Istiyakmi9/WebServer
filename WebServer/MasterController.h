#pragma once

#include "BaseController.h"
#include"ApplicationConfig.h"

class MasterController : public BaseController<MasterController>
{
private:
	ApplicationConfig* applicationConfig = nullptr;
	std::string path;
public:
	MasterController() {
		applicationConfig = ApplicationConfig::getInstance();
		path = applicationConfig->getConnectionString();

		add("PageMasterData", bind(&MasterController::PageMasterData, this, _1));
		add("AddOrUpdateCatagory", bind(&MasterController::AddOrUpdateCatagory, this, _1));
	}

	std::string PageMasterData(std::string);
	std::string AddOrUpdateCatagory(std::string);
};

