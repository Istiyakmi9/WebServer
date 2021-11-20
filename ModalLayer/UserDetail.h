
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

enum class UserDetailFuncNames {
	setAccessUid, setAddress, setAlternetNo, setCity, setCreatedOn, setCustBankAccountNo, setDoJ, setDob, setEmail, setFirstName, setIFSCCode, setLastName, setMobile, setPassword, setRoleId, setShopUid, setState, setUserUid, setUsername, setLoginId
};

class DECLSPEC UserDetail
{
private:
	int loginId;
	int UserUid;
	std::string Username;
	std::string Password;
	std::string Mobile;
	std::string Email;
	std::string FirstName;
	std::string LastName;
	std::string Address;
	std::string Dob;
	std::string DoJ;
	std::string State;
	std::string City;
	std::string CustBankAccountNo;
	std::string IFSCCode;
	std::string AlternetNo;
	std::string CreatedOn;
	int ShopUid;
	int AccessUid;
	int RoleId;

public:
	UserDetail(std::string);
	std::string getUserName();
	std::string getPassword();

	int getAccessUid();
	void setAccessUid(int value);

	std::string getAddress();
	void setAddress(std::string value);

	std::string getAlternetNo();
	void setAlternetNo(std::string value);

	std::string getCity();
	void setCity(std::string value);

	std::string getCreatedOn();
	void setCreatedOn(std::string value);

	std::string getCustBankAccountNo();
	void setCustBankAccountNo(std::string value);

	std::string getDoJ();
	void setDoJ(std::string value);

	std::string getDob();
	void setDob(std::string value);

	std::string getEmail();
	void setEmail(std::string value);

	std::string getFirstName();
	void setFirstName(std::string value);

	std::string getIFSCCode();
	void setIFSCCode(std::string value);

	std::string getLastName();
	void setLastName(std::string value);

	std::string getMobile();
	void setMobile(std::string value);
	void setPassword(std::string value);

	int getRoleId();
	void setRoleId(int value);

	int getShopUid();
	void setShopUid(int value);

	std::string getState();
	void setState(std::string value);

	int getUserUid();
	void setUserUid(int value);

	std::string getUsername();
	void setUsername(std::string value);

	int getLoginId();
	void setLoginId(int value);
	void setPrivateFieldsValue(std::string);
};