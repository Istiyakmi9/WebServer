


#pragma once

#ifdef USERDETAIL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<map>
#include"JsonManager.h"
/*--------- Method names enum -----------*/

enum class FuncNames {
	setIsClient, setAccessUid, setAddress, setAlternetMobileNo, setBankAccountNo, setCity, setCreatedOn, setDoJ, setDob, setEmail, setFirstName, setGSTNo, setIFSCCode, setImagePath, setLastName, setLicenseNo, setLoginId, setMobile, setPassword, setPincode, setRoleId, setShopName, setShopPhoneNumber, setShopUid, setState, setUserUid, setUsername
};

class DECLSPEC UserDetail
{
private:
	int LoginId;
	int UserUid;
	std::string Username;
	std::string Password;
	std::string Mobile;
	std::string Email;
	std::string FirstName;
	std::string LastName;
	std::string Address;
	std::string ShopPhoneNumber;
	std::string ShopName;
	std::string LicenseNo;
	std::string GSTNo;
	std::string Dob;
	std::string DoJ;
	std::string State;
	std::string City;
	long Pincode;
	std::string ImagePath;
	std::string BankAccountNo;
	std::string IFSCCode;
	std::string AlternetMobileNo;
	std::string CreatedOn;
	bool IsClient;
	int ShopUid;
	int AccessUid;
	int RoleId;

public:
	UserDetail(){ }	

	bool getIsClient();
	void setIsClient(bool value);

	int getAccessUid();
	void setAccessUid(int value);

	std::string getAddress();
	void setAddress(std::string value);

	std::string getAlternetMobileNo();
	void setAlternetMobileNo(std::string value);

	std::string getBankAccountNo();
	void setBankAccountNo(std::string value);

	std::string getCity();
	void setCity(std::string value);

	std::string getCreatedOn();
	void setCreatedOn(std::string value);

	std::string getDoJ();
	void setDoJ(std::string value);

	std::string getDob();
	void setDob(std::string value);

	std::string getEmail();
	void setEmail(std::string value);

	std::string getFirstName();
	void setFirstName(std::string value);

	std::string getGSTNo();
	void setGSTNo(std::string value);

	std::string getIFSCCode();
	void setIFSCCode(std::string value);

	std::string getImagePath();
	void setImagePath(std::string value);

	std::string getLastName();
	void setLastName(std::string value);

	std::string getLicenseNo();
	void setLicenseNo(std::string value);

	int getLoginId();
	void setLoginId(int value);

	std::string getMobile();
	void setMobile(std::string value);

	std::string getPassword();
	void setPassword(std::string value);

	long getPincode();
	void setPincode(long value);

	int getRoleId();
	void setRoleId(int value);

	std::string getShopName();
	void setShopName(std::string value);

	std::string getShopPhoneNumber();
	void setShopPhoneNumber(std::string value);

	int getShopUid();
	void setShopUid(int value);

	std::string getState();
	void setState(std::string value);

	int getUserUid();
	void setUserUid(int value);

	std::string getUsername();
	void setUsername(std::string value);
	void setPrivateFieldsValue(std::string);
};