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
	std::string userName;
	std::string password;
	std::string mobile;
	std::string email;
	int roleId;

public:
	UserDetail(int loginId,
		std::string userName,
		std::string password,
		std::string mobile,
		std::string Eemail,
		int roleId);
};

