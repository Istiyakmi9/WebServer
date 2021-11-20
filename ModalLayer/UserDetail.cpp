#include"UserDetail.h"

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

int UserDetail::getAccessUid() { 
	return AccessUid;
}

void UserDetail::setAccessUid(int value) { 
	AccessUid = value;
}

std::string UserDetail::getAddress() { 
	return Address;
}

void UserDetail::setAddress(std::string value) { 
	Address = value;
}

std::string UserDetail::getAlternetNo() { 
	return AlternetNo;
}

void UserDetail::setAlternetNo(std::string value) { 
	AlternetNo = value;
}

std::string UserDetail::getCity() { 
	return City;
}

void UserDetail::setCity(std::string value) { 
	City = value;
}

std::string UserDetail::getCreatedOn() { 
	return CreatedOn;
}

void UserDetail::setCreatedOn(std::string value) { 
	CreatedOn = value;
}

std::string UserDetail::getCustBankAccountNo() { 
	return CustBankAccountNo;
}

void UserDetail::setCustBankAccountNo(std::string value) { 
	CustBankAccountNo = value;
}

std::string UserDetail::getDoJ() { 
	return DoJ;
}

void UserDetail::setDoJ(std::string value) { 
	DoJ = value;
}

std::string UserDetail::getDob() { 
	return Dob;
}

void UserDetail::setDob(std::string value) { 
	Dob = value;
}

std::string UserDetail::getEmail() { 
	return Email;
}

void UserDetail::setEmail(std::string value) { 
	Email = value;
}

std::string UserDetail::getFirstName() { 
	return FirstName;
}

void UserDetail::setFirstName(std::string value) { 
	FirstName = value;
}

std::string UserDetail::getIFSCCode() { 
	return IFSCCode;
}

void UserDetail::setIFSCCode(std::string value) { 
	IFSCCode = value;
}

std::string UserDetail::getLastName() { 
	return LastName;
}

void UserDetail::setLastName(std::string value) { 
	LastName = value;
}

std::string UserDetail::getMobile() { 
	return Mobile;
}

void UserDetail::setMobile(std::string value) { 
	Mobile = value;
}

void UserDetail::setPassword(std::string value) { 
	Password = value;
}

int UserDetail::getRoleId() { 
	return RoleId;
}

void UserDetail::setRoleId(int value) { 
	RoleId = value;
}

int UserDetail::getShopUid() { 
	return ShopUid;
}

void UserDetail::setShopUid(int value) { 
	ShopUid = value;
}

std::string UserDetail::getState() { 
	return State;
}

void UserDetail::setState(std::string value) { 
	State = value;
}

int UserDetail::getUserUid() { 
	return UserUid;
}

void UserDetail::setUserUid(int value) { 
	UserUid = value;
}

std::string UserDetail::getUsername() { 
	return Username;
}

void UserDetail::setUsername(std::string value) { 
	Username = value;
}

int UserDetail::getLoginId() { 
	return loginId;
}

void UserDetail::setLoginId(int value) { 
	loginId = value;
}




void UserDetail::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, UserDetailFuncNames>> FuncIds(new std::map<std::string, UserDetailFuncNames>());
	FuncIds->insert({ "setAccessUid", UserDetailFuncNames::setAccessUid });
	FuncIds->insert({ "setAddress", UserDetailFuncNames::setAddress });
	FuncIds->insert({ "setAlternetNo", UserDetailFuncNames::setAlternetNo });
	FuncIds->insert({ "setCity", UserDetailFuncNames::setCity });
	FuncIds->insert({ "setCreatedOn", UserDetailFuncNames::setCreatedOn });
	FuncIds->insert({ "setCustBankAccountNo", UserDetailFuncNames::setCustBankAccountNo });
	FuncIds->insert({ "setDoJ", UserDetailFuncNames::setDoJ });
	FuncIds->insert({ "setDob", UserDetailFuncNames::setDob });
	FuncIds->insert({ "setEmail", UserDetailFuncNames::setEmail });
	FuncIds->insert({ "setFirstName", UserDetailFuncNames::setFirstName });
	FuncIds->insert({ "setIFSCCode", UserDetailFuncNames::setIFSCCode });
	FuncIds->insert({ "setLastName", UserDetailFuncNames::setLastName });
	FuncIds->insert({ "setMobile", UserDetailFuncNames::setMobile });
	FuncIds->insert({ "setPassword", UserDetailFuncNames::setPassword });
	FuncIds->insert({ "setRoleId", UserDetailFuncNames::setRoleId });
	FuncIds->insert({ "setShopUid", UserDetailFuncNames::setShopUid });
	FuncIds->insert({ "setState", UserDetailFuncNames::setState });
	FuncIds->insert({ "setUserUid", UserDetailFuncNames::setUserUid });
	FuncIds->insert({ "setUsername", UserDetailFuncNames::setUsername });
	FuncIds->insert({ "setLoginId", UserDetailFuncNames::setLoginId });


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	UserDetailFuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		fnName[0] = std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {
			case UserDetailFuncNames::setAccessUid:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setAccessUid(value); 
				}
				break; 
			case UserDetailFuncNames::setAddress:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setAddress(value); 
				}
				break; 
			case UserDetailFuncNames::setAlternetNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setAlternetNo(value); 
				}
				break; 
			case UserDetailFuncNames::setCity:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCity(value); 
				}
				break; 
			case UserDetailFuncNames::setCreatedOn:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCreatedOn(value); 
				}
				break; 
			case UserDetailFuncNames::setCustBankAccountNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCustBankAccountNo(value); 
				}
				break; 
			case UserDetailFuncNames::setDoJ:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setDoJ(value); 
				}
				break; 
			case UserDetailFuncNames::setDob:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setDob(value); 
				}
				break; 
			case UserDetailFuncNames::setEmail:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setEmail(value); 
				}
				break; 
			case UserDetailFuncNames::setFirstName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFirstName(value); 
				}
				break; 
			case UserDetailFuncNames::setIFSCCode:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setIFSCCode(value); 
				}
				break; 
			case UserDetailFuncNames::setLastName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setLastName(value); 
				}
				break; 
			case UserDetailFuncNames::setMobile:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setMobile(value); 
				}
				break; 
			case UserDetailFuncNames::setPassword:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setPassword(value); 
				}
				break; 
			case UserDetailFuncNames::setRoleId:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setRoleId(value); 
				}
				break; 
			case UserDetailFuncNames::setShopUid:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setShopUid(value); 
				}
				break; 
			case UserDetailFuncNames::setState:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setState(value); 
				}
				break; 
			case UserDetailFuncNames::setUserUid:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setUserUid(value); 
				}
				break; 
			case UserDetailFuncNames::setUsername:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setUsername(value); 
				}
				break; 
			case UserDetailFuncNames::setLoginId:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setLoginId(value); 
				}
				break; 

			}
		}
	}
	delete requestMap;
}
