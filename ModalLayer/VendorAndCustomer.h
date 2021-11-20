
#pragma once

#ifdef VENDORANDCUSTOMER_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<map>
#include"JsonManager.h"
/*--------- Method names enum -----------*/

enum class FuncNames {
	setAlternetMobileNo, setCity, setCreatedBy, setCreatedOn, setCustomerUid, setEmailId, setFirstName, setFullAddress, setGSTNo, setGender, setImagePath, setIsClient, setIsPremium, setLastName, setLicenseNo, setMobileNo, setPincode, setShopName, setShopPhoneNumber, setSiteUrl, setState, setUpdatedBy, setUpdatedOn
};

class VendorAndCustomer
{
private:
	std::string CustomerUid;
	std::string FirstName;
	std::string LastName;
	std::string Gender;
	std::string MobileNo;
	std::string AlternetMobileNo;
	std::string ShopPhoneNumber;
	std::string EmailId;
	std::string ShopName;
	std::string FullAddress;
	std::string LicenseNo;
	std::string GSTNo;
	std::string State;
	std::string City;
	std::string Pincode;
	std::string SiteUrl;
	std::string ImagePath;
	std::string IsPremium;
	std::string CreatedOn;
	std::string UpdatedOn;
	std::string CreatedBy;
	std::string UpdatedBy;
	std::string IsClient;

public:

	std::string getAlternetMobileNo();
	void setAlternetMobileNo(std::string value);

	std::string getCity();
	void setCity(std::string value);

	std::string getCreatedBy();
	void setCreatedBy(std::string value);

	std::string getCreatedOn();
	void setCreatedOn(std::string value);

	std::string getCustomerUid();
	void setCustomerUid(std::string value);

	std::string getEmailId();
	void setEmailId(std::string value);

	std::string getFirstName();
	void setFirstName(std::string value);

	std::string getFullAddress();
	void setFullAddress(std::string value);

	std::string getGSTNo();
	void setGSTNo(std::string value);

	std::string getGender();
	void setGender(std::string value);

	std::string getImagePath();
	void setImagePath(std::string value);

	std::string getIsClient();
	void setIsClient(std::string value);

	std::string getIsPremium();
	void setIsPremium(std::string value);

	std::string getLastName();
	void setLastName(std::string value);

	std::string getLicenseNo();
	void setLicenseNo(std::string value);

	std::string getMobileNo();
	void setMobileNo(std::string value);

	std::string getPincode();
	void setPincode(std::string value);

	std::string getShopName();
	void setShopName(std::string value);

	std::string getShopPhoneNumber();
	void setShopPhoneNumber(std::string value);

	std::string getSiteUrl();
	void setSiteUrl(std::string value);

	std::string getState();
	void setState(std::string value);

	std::string getUpdatedBy();
	void setUpdatedBy(std::string value);

	std::string getUpdatedOn();
	void setUpdatedOn(std::string value);
	void setPrivateFieldsValue(std::string);
};