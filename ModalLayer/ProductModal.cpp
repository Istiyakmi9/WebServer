#include "ProductModal.h"

ProductModal::ProductModal() { 
	ExpiryDate = new tm();
}

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

long ProductModal::getAdminId() {
	return AdminId;
}

void ProductModal::setAdminId(long value) {
	AdminId = value;
}


void ProductModal::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, ProductModalFuncNames>> FuncIds(new std::map<std::string, ProductModalFuncNames>());
	FuncIds->insert({ "setActualPrice", ProductModalFuncNames::setActualPrice });
	FuncIds->insert({ "setBrandName", ProductModalFuncNames::setBranName });
	FuncIds->insert({ "setBrandUid", ProductModalFuncNames::setBrandUid });
	FuncIds->insert({ "setCGST", ProductModalFuncNames::setCGST });
	FuncIds->insert({ "setCatagoryName", ProductModalFuncNames::setCatagoryName });
	FuncIds->insert({ "setCatagoryUid", ProductModalFuncNames::setCatagoryUid });
	FuncIds->insert({ "setDescription", ProductModalFuncNames::setDescription });
	FuncIds->insert({ "setExpiryDate", ProductModalFuncNames::setExpiryDate });
	FuncIds->insert({ "setHSNNO", ProductModalFuncNames::setHSNNo });
	FuncIds->insert({ "setIGST", ProductModalFuncNames::setIGST });
	FuncIds->insert({ "setItemName", ProductModalFuncNames::setItemName });
	FuncIds->insert({ "setMRP", ProductModalFuncNames::setMRP });
	FuncIds->insert({ "setQuantity", ProductModalFuncNames::setQuantity });
	FuncIds->insert({ "setSGST", ProductModalFuncNames::setSGST });
	FuncIds->insert({ "setSellingPrice", ProductModalFuncNames::setSellingPrice });
	FuncIds->insert({ "setSerialNumber", ProductModalFuncNames::setSerialNo });
	FuncIds->insert({ "setVendorUid", ProductModalFuncNames::setVendorUid });
	FuncIds->insert({ "setExpiryDate", ProductModalFuncNames::setExpiryDate });


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	ProductModalFuncNames name;
	std::string fnName = "";
	setAdminId(1);
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		fnName = std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {
			case ProductModalFuncNames::setActualPrice:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setActualPrice(value);
			}
			break;
			case ProductModalFuncNames::setBranName:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setBranName(value);
			}
			break;
			case ProductModalFuncNames::setBrandUid:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setBrandUid(value);
			}
			break;
			case ProductModalFuncNames::setCGST:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setCGST(value);
			}
			break;
			case ProductModalFuncNames::setCatagoryName:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setCatagoryName(value);
			}
			break;
			case ProductModalFuncNames::setCatagoryUid:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setCatagoryUid(value);
			}
			break;
			case ProductModalFuncNames::setDescription:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setDescription(value);
			}
			break;
			case ProductModalFuncNames::setExpiryDate:
			{
				struct tm* value = JsonManager::ConvertToDateTime(item->second);
				setExpiryDate(value);
			}
			break;
			case ProductModalFuncNames::setHSNNo:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setHSNNo(value);
			}
			break;
			case ProductModalFuncNames::setIGST:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setIGST(value);
			}
			break;
			case ProductModalFuncNames::setItemName:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setItemName(value);
			}
			break;
			case ProductModalFuncNames::setMRP:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setMRP(value);
			}
			break;
			case ProductModalFuncNames::setQuantity:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setQuantity(value);
			}
			break;
			case ProductModalFuncNames::setSGST:
			{
				int value = JsonManager::ConvertTo<int>(item->second);
				setSGST(value);
			}
			break;
			case ProductModalFuncNames::setSellingPrice:
			{
				long value = JsonManager::ConvertTo<long>(item->second);
				setSellingPrice(value);
			}
			break;
			case ProductModalFuncNames::setSerialNo:
			{
				std::string value = JsonManager::ConvertTo<std::string>(item->second);
				setSerialNo(value);
			}
			break;
			case ProductModalFuncNames::setVendorUid:
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
