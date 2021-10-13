#include "ProductModal.h"

ProductModal::~ProductModal() {
	delete fns;
}

ProductModal::ProductModal(std::string json) {
	fns = new std::map<std::string, std::function<void(std::string arg)>>();
	fns->insert({ "CatagoryName", bind(&ProductModal::setCatagoryName, this, _1) });
	fns->insert({ "CatagoryUid", bind(&ProductModal::setCatagoryUid, this, _1) });
	fns->insert({ "Description", bind(&ProductModal::setDescription, this, _1) });
	fns->insert({ "IGST", bind(&ProductModal::setIGST, this, _1) });
	fns->insert({ "CGST", bind(&ProductModal::setCGST, this, _1) });
	fns->insert({ "SGST", bind(&ProductModal::setSGST, this, _1) });

	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		if (fns->count(item->first) > 0) {
			std::function<void(std::string arg)> fn = fns->find(item->first)->second;
			fn(item->second);
		}
	}

	std::free(requestMap);
}

void ProductModal::setCatagoryName(std::string catagoryName) {
	this->CatagoryName = catagoryName;
}

std::string ProductModal::getCatagoryName() {
	return this->CatagoryName;
}

void ProductModal::setCatagoryUid(std::string catagoryUid) {
	if (catagoryUid != "")
		this->CatagoryUid = stoi(catagoryUid);
	else
		this->CatagoryUid = 0;
}

long ProductModal::getCatagoryUid() {
	return this->CatagoryUid;
}

void ProductModal::setDescription(std::string Description) {
	this->Description = Description;
}

std::string ProductModal::getDescription() {
	return this->Description;
}

void ProductModal::setIGST(std::string IGST) {
	if (IGST != "")
		this->IGST = stoi(IGST);
	else
		this->IGST = 0;
}

int ProductModal::getIGST() {
	return this->IGST;
}

void ProductModal::setCGST(std::string CGST) {
	if (CGST != "")
		this->CGST = stoi(CGST);
	else
		this->CGST = 0;
}

int ProductModal::getCGST() {
	return this->CGST;
}

void ProductModal::setSGST(std::string SGST) {
	if (SGST != "")
		this->SGST = stoi(SGST);
	else
		this->SGST = 0;
}
int ProductModal::getSGST() {
	return this->SGST;
}