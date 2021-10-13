#pragma once

#ifdef USERDETAIL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>

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
};

