
#pragma once

#ifdef CATAGORYMODAL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<map>
#include"JsonManager.h"
/*--------- Method names enum -----------*/

enum class FuncNames {
	setAddedOn, setAdminId, setCGST, setCatagoryName, setCatagoryUid, setDescription, setIGST, setParentCatagoryUid, setSGST, setUpdateOn
};

class CatagoryModal
{
private:
	long CatagoryUid;
	long ParentCatagoryUid;
	std::string CatagoryName;
	std::string Description;
	std::string AddedOn;
	std::string UpdateOn;
	int CGST;
	int SGST;
	int IGST;
	long AdminId;

public:
	CatagoryModal() {}

	std::string getAddedOn();
	void setAddedOn(std::string value);

	long getAdminId();
	void setAdminId(long value);

	int getCGST();
	void setCGST(int value);

	std::string getCatagoryName();
	void setCatagoryName(std::string value);

	long getCatagoryUid();
	void setCatagoryUid(long value);

	std::string getDescription();
	void setDescription(std::string value);

	int getIGST();
	void setIGST(int value);

	long getParentCatagoryUid();
	void setParentCatagoryUid(long value);

	int getSGST();
	void setSGST(int value);

	std::string getUpdateOn();
	void setUpdateOn(std::string value);
	void setPrivateFieldsValue(std::string);
};