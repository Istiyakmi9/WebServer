#include"VendorAndCustomer.h"

std::string VendorAndCustomer::getAlternetMobileNo() { 
	return AlternetMobileNo;
}

void VendorAndCustomer::setAlternetMobileNo(std::string value) { 
	AlternetMobileNo = value;
}

std::string VendorAndCustomer::getCity() { 
	return City;
}

void VendorAndCustomer::setCity(std::string value) { 
	City = value;
}

std::string VendorAndCustomer::getCreatedBy() { 
	return CreatedBy;
}

void VendorAndCustomer::setCreatedBy(std::string value) { 
	CreatedBy = value;
}

std::string VendorAndCustomer::getCreatedOn() { 
	return CreatedOn;
}

void VendorAndCustomer::setCreatedOn(std::string value) { 
	CreatedOn = value;
}

std::string VendorAndCustomer::getCustomerUid() { 
	return CustomerUid;
}

void VendorAndCustomer::setCustomerUid(std::string value) { 
	CustomerUid = value;
}

std::string VendorAndCustomer::getEmailId() { 
	return EmailId;
}

void VendorAndCustomer::setEmailId(std::string value) { 
	EmailId = value;
}

std::string VendorAndCustomer::getFirstName() { 
	return FirstName;
}

void VendorAndCustomer::setFirstName(std::string value) { 
	FirstName = value;
}

std::string VendorAndCustomer::getFullAddress() { 
	return FullAddress;
}

void VendorAndCustomer::setFullAddress(std::string value) { 
	FullAddress = value;
}

std::string VendorAndCustomer::getGSTNo() { 
	return GSTNo;
}

void VendorAndCustomer::setGSTNo(std::string value) { 
	GSTNo = value;
}

std::string VendorAndCustomer::getGender() { 
	return Gender;
}

void VendorAndCustomer::setGender(std::string value) { 
	Gender = value;
}

std::string VendorAndCustomer::getImagePath() { 
	return ImagePath;
}

void VendorAndCustomer::setImagePath(std::string value) { 
	ImagePath = value;
}

std::string VendorAndCustomer::getIsClient() { 
	return IsClient;
}

void VendorAndCustomer::setIsClient(std::string value) { 
	IsClient = value;
}

std::string VendorAndCustomer::getIsPremium() { 
	return IsPremium;
}

void VendorAndCustomer::setIsPremium(std::string value) { 
	IsPremium = value;
}

std::string VendorAndCustomer::getLastName() { 
	return LastName;
}

void VendorAndCustomer::setLastName(std::string value) { 
	LastName = value;
}

std::string VendorAndCustomer::getLicenseNo() { 
	return LicenseNo;
}

void VendorAndCustomer::setLicenseNo(std::string value) { 
	LicenseNo = value;
}

std::string VendorAndCustomer::getMobileNo() { 
	return MobileNo;
}

void VendorAndCustomer::setMobileNo(std::string value) { 
	MobileNo = value;
}

std::string VendorAndCustomer::getPincode() { 
	return Pincode;
}

void VendorAndCustomer::setPincode(std::string value) { 
	Pincode = value;
}

std::string VendorAndCustomer::getShopName() { 
	return ShopName;
}

void VendorAndCustomer::setShopName(std::string value) { 
	ShopName = value;
}

std::string VendorAndCustomer::getShopPhoneNumber() { 
	return ShopPhoneNumber;
}

void VendorAndCustomer::setShopPhoneNumber(std::string value) { 
	ShopPhoneNumber = value;
}

std::string VendorAndCustomer::getSiteUrl() { 
	return SiteUrl;
}

void VendorAndCustomer::setSiteUrl(std::string value) { 
	SiteUrl = value;
}

std::string VendorAndCustomer::getState() { 
	return State;
}

void VendorAndCustomer::setState(std::string value) { 
	State = value;
}

std::string VendorAndCustomer::getUpdatedBy() { 
	return UpdatedBy;
}

void VendorAndCustomer::setUpdatedBy(std::string value) { 
	UpdatedBy = value;
}

std::string VendorAndCustomer::getUpdatedOn() { 
	return UpdatedOn;
}

void VendorAndCustomer::setUpdatedOn(std::string value) { 
	UpdatedOn = value;
}




void VendorAndCustomer::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());
	FuncIds->insert({ "setAlternetMobileNo", FuncNames::setAlternetMobileNo });
	FuncIds->insert({ "setCity", FuncNames::setCity });
	FuncIds->insert({ "setCreatedBy", FuncNames::setCreatedBy });
	FuncIds->insert({ "setCreatedOn", FuncNames::setCreatedOn });
	FuncIds->insert({ "setCustomerUid", FuncNames::setCustomerUid });
	FuncIds->insert({ "setEmailId", FuncNames::setEmailId });
	FuncIds->insert({ "setFirstName", FuncNames::setFirstName });
	FuncIds->insert({ "setFullAddress", FuncNames::setFullAddress });
	FuncIds->insert({ "setGSTNo", FuncNames::setGSTNo });
	FuncIds->insert({ "setGender", FuncNames::setGender });
	FuncIds->insert({ "setImagePath", FuncNames::setImagePath });
	FuncIds->insert({ "setIsClient", FuncNames::setIsClient });
	FuncIds->insert({ "setIsPremium", FuncNames::setIsPremium });
	FuncIds->insert({ "setLastName", FuncNames::setLastName });
	FuncIds->insert({ "setLicenseNo", FuncNames::setLicenseNo });
	FuncIds->insert({ "setMobileNo", FuncNames::setMobileNo });
	FuncIds->insert({ "setPincode", FuncNames::setPincode });
	FuncIds->insert({ "setShopName", FuncNames::setShopName });
	FuncIds->insert({ "setShopPhoneNumber", FuncNames::setShopPhoneNumber });
	FuncIds->insert({ "setSiteUrl", FuncNames::setSiteUrl });
	FuncIds->insert({ "setState", FuncNames::setState });
	FuncIds->insert({ "setUpdatedBy", FuncNames::setUpdatedBy });
	FuncIds->insert({ "setUpdatedOn", FuncNames::setUpdatedOn });


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
			case FuncNames::setAlternetMobileNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setAlternetMobileNo(value); 
				}
				break; 
			case FuncNames::setCity:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCity(value); 
				}
				break; 
			case FuncNames::setCreatedBy:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCreatedBy(value); 
				}
				break; 
			case FuncNames::setCreatedOn:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCreatedOn(value); 
				}
				break; 
			case FuncNames::setCustomerUid:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCustomerUid(value); 
				}
				break; 
			case FuncNames::setEmailId:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setEmailId(value); 
				}
				break; 
			case FuncNames::setFirstName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFirstName(value); 
				}
				break; 
			case FuncNames::setFullAddress:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFullAddress(value); 
				}
				break; 
			case FuncNames::setGSTNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setGSTNo(value); 
				}
				break; 
			case FuncNames::setGender:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setGender(value); 
				}
				break; 
			case FuncNames::setImagePath:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setImagePath(value); 
				}
				break; 
			case FuncNames::setIsClient:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setIsClient(value); 
				}
				break; 
			case FuncNames::setIsPremium:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setIsPremium(value); 
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
			case FuncNames::setMobileNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setMobileNo(value); 
				}
				break; 
			case FuncNames::setPincode:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setPincode(value); 
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
			case FuncNames::setSiteUrl:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setSiteUrl(value); 
				}
				break; 
			case FuncNames::setState:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setState(value); 
				}
				break; 
			case FuncNames::setUpdatedBy:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setUpdatedBy(value); 
				}
				break; 
			case FuncNames::setUpdatedOn:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setUpdatedOn(value); 
				}
				break; 

			}
		}
	}
	delete requestMap;
}
