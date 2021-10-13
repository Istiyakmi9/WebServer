#include "UserDetail.h"
#include"JsonManager.h"
#include <iostream>
#include <string>

UserDetail::UserDetail(std::string json) {
	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	std::map<std::string, std::string>::iterator itr;
	for (itr = requestMap->begin(); itr != requestMap->end(); itr++) {
		if (itr->first == "loginId")
			loginId = stoi(itr->second);
		else if (itr->first == "UserUid")
			UserUid = stoi(itr->second);
		else if (itr->first == "Username")
			Username = itr->second;
		else if (itr->first == "Password")
			Password = itr->second;
		else if (itr->first == "Mobile")
			Mobile = itr->second;
		else if (itr->first == "Email")
			Email = itr->second;
		else if (itr->first == "FirstName")
			FirstName = itr->second;
		else if (itr->first == "LastName")
			LastName = itr->second;
		else if (itr->first == "Address")
			Address = itr->second;
		else if (itr->first == "Dob")
			Dob = itr->second;
		else if (itr->first == "DoJ")
			DoJ = itr->second;
		else if (itr->first == "State")
			State = itr->second;
		else if (itr->first == "City")
			City = itr->second;
		else if (itr->first == "CustBankAccountNo")
			CustBankAccountNo = itr->second;
		else if (itr->first == "IFSCCode")
			IFSCCode = itr->second;
		else if (itr->first == "AlternetNo")
			AlternetNo = itr->second;
		else if (itr->first == "CreatedOn")
			CreatedOn = itr->second;
		else if (itr->first == "ShopUid")
			ShopUid = stoi(itr->second);
		else if (itr->first == "AccessUid")
			AccessUid = stoi(itr->second);
		else if (itr->first == "RoleId")
			RoleId = stoi(itr->second);
	}

	std::free(requestMap);
}

std::string UserDetail::getUserName() {
	return this->Username;
}

std::string UserDetail::getPassword() {
	return this->Password;
}