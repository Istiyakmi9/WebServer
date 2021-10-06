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
	std::string Username;
	std::string Password;
	std::string Mobile;
	std::string Email;
	int RoleId;

public:
	UserDetail(std::string);
	std::string getUserName();
	std::string getPassword();
};

