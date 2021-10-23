#include "ProductModal.h"


ProductModal::ProductModal() { }

ProductModal::~ProductModal() {
	delete ExpiryDate;
}

long ProductModal::getActualPrice() { 
	return ActualPrice;
}

void ProductModal::setActualPrice(long value) { 
	ActualPrice = value;
}

std::string ProductModal::getBranName() { 
	return BranName;
}

void ProductModal::setBranName(std::string value) { 
	BranName = value;
}

long ProductModal::getBrandUid() { 
	return BrandUid;
}

void ProductModal::setBrandUid(long value) { 
	BrandUid = value;
}

int ProductModal::getCGST() { 
	return CGST;
}

void ProductModal::setCGST(int value) { 
	CGST = value;
}

std::string ProductModal::getCatagoryName() { 
	return CatagoryName;
}

void ProductModal::setCatagoryName(std::string value) { 
	CatagoryName = value;
}

long ProductModal::getCatagoryUid() { 
	return CatagoryUid;
}

void ProductModal::setCatagoryUid(long value) { 
	CatagoryUid = value;
}

std::string ProductModal::getDescription() { 
	return Description;
}

void ProductModal::setDescription(std::string value) { 
	Description = value;
}

struct tm* ProductModal::getExpiryDate() { 
	return ExpiryDate;
}

void ProductModal::setExpiryDate(struct tm* value) { 
	ExpiryDate = value;
}

std::string ProductModal::getHSNNo() { 
	return HSNNo;
}

void ProductModal::setHSNNo(std::string value) { 
	HSNNo = value;
}

int ProductModal::getIGST() { 
	return IGST;
}

void ProductModal::setIGST(int value) { 
	IGST = value;
}

std::string ProductModal::getItemName() { 
	return ItemName;
}

void ProductModal::setItemName(std::string value) { 
	ItemName = value;
}

long ProductModal::getMRP() { 
	return MRP;
}

void ProductModal::setMRP(long value) { 
	MRP = value;
}

int ProductModal::getQuantity() { 
	return Quantity;
}

void ProductModal::setQuantity(int value) { 
	Quantity = value;
}

int ProductModal::getSGST() { 
	return SGST;
}

void ProductModal::setSGST(int value) { 
	SGST = value;
}

long ProductModal::getSellingPrice() { 
	return SellingPrice;
}

void ProductModal::setSellingPrice(long value) { 
	SellingPrice = value;
}

std::string ProductModal::getSerialNo() { 
	return SerialNo;
}

void ProductModal::setSerialNo(std::string value) { 
	SerialNo = value;
}

long ProductModal::getVendorUid() { 
	return VendorUid;
}

void ProductModal::setVendorUid(long value) { 
	VendorUid = value;
}


void ProductModal::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());
	FuncIds->insert({ "setActualPrice", FuncNames::setActualPrice });
	FuncIds->insert({ "setBranName", FuncNames::setBranName });
	FuncIds->insert({ "setBrandUid", FuncNames::setBrandUid });
	FuncIds->insert({ "setCGST", FuncNames::setCGST });
	FuncIds->insert({ "setCatagoryName", FuncNames::setCatagoryName });
	FuncIds->insert({ "setCatagoryUid", FuncNames::setCatagoryUid });
	FuncIds->insert({ "setDescription", FuncNames::setDescription });
	FuncIds->insert({ "setExpiryDate", FuncNames::setExpiryDate });
	FuncIds->insert({ "setHSNNo", FuncNames::setHSNNo });
	FuncIds->insert({ "setIGST", FuncNames::setIGST });
	FuncIds->insert({ "setItemName", FuncNames::setItemName });
	FuncIds->insert({ "setMRP", FuncNames::setMRP });
	FuncIds->insert({ "setQuantity", FuncNames::setQuantity });
	FuncIds->insert({ "setSGST", FuncNames::setSGST });
	FuncIds->insert({ "setSellingPrice", FuncNames::setSellingPrice });
	FuncIds->insert({ "setSerialNo", FuncNames::setSerialNo });
	FuncIds->insert({ "setVendorUid", FuncNames::setVendorUid });


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	FuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {
			case FuncNames::setActualPrice:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setActualPrice(value); 
				}
				break; 
			case FuncNames::setBranName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setBranName(value); 
				}
				break; 
			case FuncNames::setBrandUid:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setBrandUid(value); 
				}
				break; 
			case FuncNames::setCGST:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setCGST(value); 
				}
				break; 
			case FuncNames::setCatagoryName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setCatagoryName(value); 
				}
				break; 
			case FuncNames::setCatagoryUid:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setCatagoryUid(value); 
				}
				break; 
			case FuncNames::setDescription:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setDescription(value); 
				}
				break; 
			case FuncNames::setExpiryDate:
				{
					struct tm* value = JsonManager::ConvertToDateTime(item->second);
					setExpiryDate(value); 
				}
				break; 
			case FuncNames::setHSNNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setHSNNo(value); 
				}
				break; 
			case FuncNames::setIGST:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setIGST(value); 
				}
				break; 
			case FuncNames::setItemName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setItemName(value); 
				}
				break; 
			case FuncNames::setMRP:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setMRP(value); 
				}
				break; 
			case FuncNames::setQuantity:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setQuantity(value); 
				}
				break; 
			case FuncNames::setSGST:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setSGST(value); 
				}
				break; 
			case FuncNames::setSellingPrice:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setSellingPrice(value); 
				}
				break; 
			case FuncNames::setSerialNo:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setSerialNo(value); 
				}
				break; 
			case FuncNames::setVendorUid:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setVendorUid(value); 
				}
				break; 

			}
		}
	}
	delete requestMap;
}
