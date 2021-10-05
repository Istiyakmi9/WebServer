#include "UserDetail.h"

UserDetail::UserDetail(int loginId,
	std::string userName,
	std::string password,
	std::string mobile,
	std::string email,
	int roleId) {
	this->loginId = loginId;
	this->userName = userName;
	this->password = "";
	this->mobile = mobile;
	this->email = email;
	this->roleId = roleId;
}