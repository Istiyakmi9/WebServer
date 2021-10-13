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

using std::placeholders::_1;
using std::bind;

class DECLSPEC ProductModal
{
private:
	std::string CatagoryName;
	long CatagoryUid;
	std::string Description;
	int IGST;
	int CGST;
	int SGST;

	std::map<std::string, std::function<void(std::string arg)>>* fns;

public:
	ProductModal(std::string json);
	~ProductModal();

	void setCatagoryName(std::string catagoryName);
	std::string getCatagoryName();
	
	void setCatagoryUid(std::string catagoryUid);
	long getCatagoryUid();
	
	void setDescription(std::string Description);
	std::string getDescription();

	void setIGST(std::string IGST);
	int getIGST();

	void setCGST(std::string CGST);
	int getCGST();

	void setSGST(std::string SGST);
	int getSGST();
};