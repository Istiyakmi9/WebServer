#pragma once

#include<iostream>
#include<unordered_map>

#include"ProductModal.h"
#include"UserDetail.h"

enum class Class {
	ProductModal = 1,
	UserDetail
};

class classDetail {
private:
	int catagory;
	std::vector<std::string> argsType[5];

public:
	void setCatagory() {

	}
};

class metacontainer 
{
private:
	std::unordered_map<Class, classDetail> *meta;

public:
	metacontainer() {
		meta = new std::unordered_map<Class, classDetail>();
	}

	~metacontainer() {
		delete meta;
	}

	void loadClasses() {
		//meta->insert({ Class::ProductModal,  });
		//meta->insert({ Class::UserDetail, "" });
	}
};