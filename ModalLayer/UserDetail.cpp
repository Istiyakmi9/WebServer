#include"UserDetail.h"


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

std::string UserDetail::getAlternetMobileNo() {
	return AlternetMobileNo;
}

void UserDetail::setAlternetMobileNo(std::string value) {
	AlternetMobileNo = value;
}

std::string UserDetail::getBankAccountNo() {
	return BankAccountNo;
}

void UserDetail::setBankAccountNo(std::string value) {
	BankAccountNo = value;
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

std::string UserDetail::getGSTNo() {
	return GSTNo;
}

void UserDetail::setGSTNo(std::string value) {
	GSTNo = value;
}

std::string UserDetail::getIFSCCode() {
	return IFSCCode;
}

void UserDetail::setIFSCCode(std::string value) {
	IFSCCode = value;
}

std::string UserDetail::getImagePath() {
	return ImagePath;
}

void UserDetail::setImagePath(std::string value) {
	ImagePath = value;
}

std::string UserDetail::getLastName() {
	return LastName;
}

void UserDetail::setLastName(std::string value) {
	LastName = value;
}

std::string UserDetail::getLicenseNo() {
	return LicenseNo;
}

void UserDetail::setLicenseNo(std::string value) {
	LicenseNo = value;
}

int UserDetail::getLoginId() {
	return LoginId;
}

void UserDetail::setLoginId(int value) {
	LoginId = value;
}

std::string UserDetail::getMobile() {
	return Mobile;
}

void UserDetail::setMobile(std::string value) {
	Mobile = value;
}

std::string UserDetail::getPassword() {
	return Password;
}

void UserDetail::setPassword(std::string value) {
	Password = value;
}

long UserDetail::getPincode() {
	return Pincode;
}

void UserDetail::setPincode(long value) {
	Pincode = value;
}

int UserDetail::getRoleId() {
	return RoleId;
}

void UserDetail::setRoleId(int value) {
	RoleId = value;
}

std::string UserDetail::getShopName() {
	return ShopName;
}

void UserDetail::setShopName(std::string value) {
	ShopName = value;
}

std::string UserDetail::getShopPhoneNumber() {
	return ShopPhoneNumber;
}

void UserDetail::setShopPhoneNumber(std::string value) {
	ShopPhoneNumber = value;
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

bool UserDetail::getIsClient() {
	return IsClient;
}

void UserDetail::setIsClient(bool value) {
	IsClient = value;
}

int UserDetail::getExistingFileDetailId() {
	return ExistingFileDetailId;
}

void UserDetail::setExistingFileDetailId(int value) {
	ExistingFileDetailId = value;
}



void UserDetail::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());
	FuncIds->insert({ "setAccessUid", FuncNames::setAccessUid });
	FuncIds->insert({ "setAddress", FuncNames::setAddress });
	FuncIds->insert({ "setAlternetMobileNo", FuncNames::setAlternetMobileNo });
	FuncIds->insert({ "setBankAccountNo", FuncNames::setBankAccountNo });
	FuncIds->insert({ "setCity", FuncNames::setCity });
	FuncIds->insert({ "setCreatedOn", FuncNames::setCreatedOn });
	FuncIds->insert({ "setDoJ", FuncNames::setDoJ });
	FuncIds->insert({ "setDob", FuncNames::setDob });
	FuncIds->insert({ "setEmail", FuncNames::setEmail });
	FuncIds->insert({ "setFirstName", FuncNames::setFirstName });
	FuncIds->insert({ "setGSTNo", FuncNames::setGSTNo });
	FuncIds->insert({ "setIFSCCode", FuncNames::setIFSCCode });
	FuncIds->insert({ "setImagePath", FuncNames::setImagePath });
	FuncIds->insert({ "setLastName", FuncNames::setLastName });
	FuncIds->insert({ "setLicenseNo", FuncNames::setLicenseNo });
	FuncIds->insert({ "setLoginId", FuncNames::setLoginId });
	FuncIds->insert({ "setMobile", FuncNames::setMobile });
	FuncIds->insert({ "setPassword", FuncNames::setPassword });
	FuncIds->insert({ "setPincode", FuncNames::setPincode });
	FuncIds->insert({ "setRoleId", FuncNames::setRoleId });
	FuncIds->insert({ "setShopName", FuncNames::setShopName });
	FuncIds->insert({ "setShopPhoneNumber", FuncNames::setShopPhoneNumber });
	FuncIds->insert({ "setShopUid", FuncNames::setShopUid });
	FuncIds->insert({ "setState", FuncNames::setState });
	FuncIds->insert({ "setUserUid", FuncNames::setUserUid });
	FuncIds->insert({ "setUsername", FuncNames::setUsername });
	FuncIds->insert({ "setIsClient", FuncNames::setIsClient });
	FuncIds->insert({ "setExistingFileDetailId", FuncNames::setExistingFileDetailId });


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
			case FuncNames::setExistingFileDetailId:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setExistingFileDetailId(value);
			}
			case FuncNames::setIsClient:
			{
				bool value = JsonManager::ConvertTo<bool>(item->second);
				setAccessUid(value);
			}
			break;
			case FuncNames::setAccessUid:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setAccessUid(value);
			}
			break;
			case FuncNames::setAddress:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setAddress(value);
			}
			break;
			case FuncNames::setAlternetMobileNo:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setAlternetMobileNo(value);
			}
			break;
			case FuncNames::setBankAccountNo:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setBankAccountNo(value);
			}
			break;
			case FuncNames::setCity:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setCity(value);
			}
			break;
			case FuncNames::setCreatedOn:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setCreatedOn(value);
			}
			break;
			case FuncNames::setDoJ:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setDoJ(value);
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
			case FuncNames::setIFSCCode:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setIFSCCode(value);
			}
			break;
			case FuncNames::setImagePath:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setImagePath(value);
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
			case FuncNames::setPincode:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setPincode(value);
			}
			break;
			case FuncNames::setRoleId:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setRoleId(value);
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
			case FuncNames::setShopUid:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setShopUid(value);
			}
			break;
			case FuncNames::setState:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setState(value);
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
