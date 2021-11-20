#include"CatagoryModal.h"

std::string CatagoryModal::getAddedOn() { 
	return AddedOn;
}

void CatagoryModal::setAddedOn(std::string value) { 
	AddedOn = value;
}

long CatagoryModal::getAdminId() { 
	return AdminId;
}

void CatagoryModal::setAdminId(long value) { 
	AdminId = value;
}

int CatagoryModal::getCGST() { 
	return CGST;
}

void CatagoryModal::setCGST(int value) { 
	CGST = value;
}

std::string CatagoryModal::getCatagoryName() { 
	return CatagoryName;
}

void CatagoryModal::setCatagoryName(std::string value) { 
	CatagoryName = value;
}

long CatagoryModal::getCatagoryUid() { 
	return CatagoryUid;
}

void CatagoryModal::setCatagoryUid(long value) { 
	CatagoryUid = value;
}

std::string CatagoryModal::getDescription() { 
	return Description;
}

void CatagoryModal::setDescription(std::string value) { 
	Description = value;
}

int CatagoryModal::getIGST() { 
	return IGST;
}

void CatagoryModal::setIGST(int value) { 
	IGST = value;
}

long CatagoryModal::getParentCatagoryUid() { 
	return ParentCatagoryUid;
}

void CatagoryModal::setParentCatagoryUid(long value) { 
	ParentCatagoryUid = value;
}

int CatagoryModal::getSGST() { 
	return SGST;
}

void CatagoryModal::setSGST(int value) { 
	SGST = value;
}

std::string CatagoryModal::getUpdateOn() { 
	return UpdateOn;
}

void CatagoryModal::setUpdateOn(std::string value) { 
	UpdateOn = value;
}




void CatagoryModal::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());
	FuncIds->insert({ "setAddedOn", FuncNames::setAddedOn });
	FuncIds->insert({ "setAdminId", FuncNames::setAdminId });
	FuncIds->insert({ "setCGST", FuncNames::setCGST });
	FuncIds->insert({ "setCatagoryName", FuncNames::setCatagoryName });
	FuncIds->insert({ "setCatagoryUid", FuncNames::setCatagoryUid });
	FuncIds->insert({ "setDescription", FuncNames::setDescription });
	FuncIds->insert({ "setIGST", FuncNames::setIGST });
	FuncIds->insert({ "setParentCatagoryUid", FuncNames::setParentCatagoryUid });
	FuncIds->insert({ "setSGST", FuncNames::setSGST });
	FuncIds->insert({ "setUpdateOn", FuncNames::setUpdateOn });


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
			case FuncNames::setAddedOn:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setAddedOn(value); 
				}
				break; 
			case FuncNames::setAdminId:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setAdminId(value); 
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
			case FuncNames::setIGST:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setIGST(value); 
				}
				break; 
			case FuncNames::setParentCatagoryUid:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setParentCatagoryUid(value); 
				}
				break; 
			case FuncNames::setSGST:
				{
					int value = JsonManager::ConvertTo<int>(item->second);
					setSGST(value); 
				}
				break; 
			case FuncNames::setUpdateOn:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setUpdateOn(value); 
				}
				break; 

			}
		}
	}
	delete requestMap;
}
