
#pragma once

#include<iostream>
#include<map>
#include"JsonManager.h"
/*--------- Method names enum -----------*/

enum class FuncNames {
	setAddress, setDob, setEmail, setFirstName, setGSTNo, setLastName, setLicenseNo, setLoginId, setMobile, setPassword, setShopName, setShopPhoneNumber, setUserUid, setUsername
};

class Billing
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
	std::string getAddress();
	void setAddress(std::string value);

	std::string getDob();
	void setDob(std::string value);

	std::string getEmail();
	void setEmail(std::string value);

	std::string getFirstName();
	void setFirstName(std::string value);

	std::string getGSTNo();
	void setGSTNo(std::string value);

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

	std::string getShopName();
	void setShopName(std::string value);

	std::string getShopPhoneNumber();
	void setShopPhoneNumber(std::string value);

	int getUserUid();
	void setUserUid(int value);

	std::string getUsername();
	void setUsername(std::string value);
	void setPrivateFieldsValue(std::string);
};