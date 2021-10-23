#pragma once

#include "BaseController.h"
#include"ApplicationConfig.h"
#include"DbUtility.h"

class MasterController : public BaseController<MasterController>
{
private:
	DbUtility* dbUtility = nullptr;

public:
	MasterController() {
		dbUtility = new DbUtility();

		add("PageMasterData", bind(&MasterController::PageMasterData, this, _1));
		add("AddOrUpdateCatagory", bind(&MasterController::AddOrUpdateCatagory, this, _1));
	}

	~MasterController() {
		delete dbUtility;
	}

	std::string PageMasterData(std::string);
	std::string AddOrUpdateCatagory(std::string);
};

