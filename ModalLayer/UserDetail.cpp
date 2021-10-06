#include "UserDetail.h"
#include"JsonManager.h"

UserDetail::UserDetail(std::string json) {
	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	std::map<std::string, std::string>::iterator itr;
	for (itr = requestMap->begin(); itr != requestMap->end(); itr++) {
		if (itr->first == "Username")
			this->Username = itr->second;
		else if (itr->first == "Password")
			this->Password = itr->second;
	}

	std::free(requestMap);
}

std::string UserDetail::getUserName() {
	return this->Username;
}

std::string UserDetail::getPassword() {
	return this->Password;
}