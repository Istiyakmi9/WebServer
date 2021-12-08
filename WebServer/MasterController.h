#pragma once

#include"BaseController.h"
#include"DbUtility.h"
#include"ApplicationConfig.h"
#include"Constants.h"

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

