#include"Billing.h"

std::string Billing::getAddress() { 
	return Address;
}

void Billing::setAddress(std::string value) { 
	Address = value;
}

std::string Billing::getDob() { 
	return Dob;
}

void Billing::setDob(std::string value) { 
	Dob = value;
}

std::string Billing::getEmail() { 
	return Email;
}

void Billing::setEmail(std::string value) { 
	Email = value;
}

std::string Billing::getFirstName() { 
	return FirstName;
}

void Billing::setFirstName(std::string value) { 
	FirstName = value;
}

std::string Billing::getGSTNo() { 
	return GSTNo;
}

void Billing::setGSTNo(std::string value) { 
	GSTNo = value;
}

std::string Billing::getLastName() { 
	return LastName;
}

void Billing::setLastName(std::string value) { 
	LastName = value;
}

std::string Billing::getLicenseNo() { 
	return LicenseNo;
}

void Billing::setLicenseNo(std::string value) { 
	LicenseNo = value;
}

int Billing::getLoginId() { 
	return LoginId;
}

void Billing::setLoginId(int value) { 
	LoginId = value;
}

std::string Billing::getMobile() { 
	return Mobile;
}

void Billing::setMobile(std::string value) { 
	Mobile = value;
}

std::string Billing::getPassword() { 
	return Password;
}

void Billing::setPassword(std::string value) { 
	Password = value;
}

std::string Billing::getShopName() { 
	return ShopName;
}

void Billing::setShopName(std::string value) { 
	ShopName = value;
}

std::string Billing::getShopPhoneNumber() { 
	return ShopPhoneNumber;
}

void Billing::setShopPhoneNumber(std::string value) { 
	ShopPhoneNumber = value;
}

int Billing::getUserUid() { 
	return UserUid;
}

void Billing::setUserUid(int value) { 
	UserUid = value;
}

std::string Billing::getUsername() { 
	return Username;
}

void Billing::setUsername(std::string value) { 
	Username = value;
}




void Billing::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());
	FuncIds->insert({ "setAddress", FuncNames::setAddress });
	FuncIds->insert({ "setDob", FuncNames::setDob });
	FuncIds->insert({ "setEmail", FuncNames::setEmail });
	FuncIds->insert({ "setFirstName", FuncNames::setFirstName });
	FuncIds->insert({ "setGSTNo", FuncNames::setGSTNo });
	FuncIds->insert({ "setLastName", FuncNames::setLastName });
	FuncIds->insert({ "setLicenseNo", FuncNames::setLicenseNo });
	FuncIds->insert({ "setLoginId", FuncNames::setLoginId });
	FuncIds->insert({ "setMobile", FuncNames::setMobile });
	FuncIds->insert({ "setPassword", FuncNames::setPassword });
	FuncIds->insert({ "setShopName", FuncNames::setShopName });
	FuncIds->insert({ "setShopPhoneNumber", FuncNames::setShopPhoneNumber });
	FuncIds->insert({ "setUserUid", FuncNames::setUserUid });
	FuncIds->insert({ "setUsername", FuncNames::setUsername });


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	FuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		fnName[0] = std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {
			case FuncNames::setAddress:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setAddress(value); 
				}
				break; 
			case FuncNames::setDob:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setDob(value); 
				}
				break; 
			case FuncNames::setEmail:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setEmail(value); 
				}
				break; 
			case FuncNames::setFirstName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFirstName(value); 
				}
				break; 
			case FuncNames::setGSTNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setGSTNo(value); 
				}
				break; 
			case FuncNames::setLastName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setLastName(value); 
				}
				break; 
			case FuncNames::setLicenseNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setLicenseNo(value); 
				}
				break; 
			case FuncNames::setLoginId:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setLoginId(value); 
				}
				break; 
			case FuncNames::setMobile:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setMobile(value); 
				}
				break; 
			case FuncNames::setPassword:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setPassword(value); 
				}
				break; 
			case FuncNames::setShopName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setShopName(value); 
				}
				break; 
			case FuncNames::setShopPhoneNumber:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setShopPhoneNumber(value); 
				}
				break; 
			case FuncNames::setUserUid:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setUserUid(value); 
				}
				break; 
			case FuncNames::setUsername:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setUsername(value); 
				}
				break; 

			}
		}
	}
	delete requestMap;
}
