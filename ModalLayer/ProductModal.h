#pragma once

#ifdef PRODUCTMODAL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<list>
#include"JsonManager.h"
#include<map>
#include<functional>
#include<string>
#include<map>
#include"JsonManager.h"
#include<map>
#include"JsonManager.h"

using std::placeholders::_1;
using std::bind;


/*--------- Method names enum -----------*/

enum class ProductModalFuncNames {
	setActualPrice, setBranName, setBrandUid, setCGST, setCatagoryName, setCatagoryUid, setDescription, setExpiryDate, setHSNNo, setIGST, setItemName, setMRP, setQuantity, setSGST, setSellingPrice, setSerialNo, setVendorUid
};

class DECLSPEC ProductModal
{
private:
	std::string CatagoryName;
	long CatagoryUid;
	std::string Description;
	int IGST;
	int CGST;
	int SGST;

	std::string ItemName;
	long VendorUid;
	std::string BranName;
	long BrandUid;
	std::string SerialNo;
	int Quantity;
	std::string HSNNo;
	long MRP;
	long ActualPrice;
	long SellingPrice;
	long AdminId;
	struct tm* ExpiryDate;

public:
	ProductModal();
	~ProductModal();

	long getAdminId();
	void setAdminId(long value);

	long getActualPrice();
	void setActualPrice(long value);

	std::string getBranName();
	void setBranName(std::string value);

	long getBrandUid();
	void setBrandUid(long value);

	int getCGST();
	void setCGST(int value);

	std::string getCatagoryName();
	void setCatagoryName(std::string value);

	long getCatagoryUid();
	void setCatagoryUid(long value);

	std::string getDescription();
	void setDescription(std::string value);

	struct tm* getExpiryDate();
	void setExpiryDate(struct tm* value);

	std::string getHSNNo();
	void setHSNNo(std::string value);

	int getIGST();
	void setIGST(int value);

	std::string getItemName();
	void setItemName(std::string value);

	long getMRP();
	void setMRP(long value);

	int getQuantity();
	void setQuantity(int value);

	int getSGST();
	void setSGST(int value);

	long getSellingPrice();
	void setSellingPrice(long value);

	std::string getSerialNo();
	void setSerialNo(std::string value);

	long getVendorUid();
	void setVendorUid(long value);
	void setPrivateFieldsValue(std::string);
};