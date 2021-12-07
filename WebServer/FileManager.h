#pragma once
#include<iostream>
#include"HttpRequest.h"
#include"DbUtility.h"
#include<FileDetail.h>

class FileManager
{
private:
	DbUtility* dbUtility;
	FileDetail* fileDetail;

public:
	FileManager();
	~FileManager();
	std::unique_ptr<FileDetail> saveHttpRequestedFile(std::string searchName, std::string path, std::string fileName, HttpRequest* httpRequest);
	std::string saveFile(std::string searchName, std::string path, std::string fileName, HttpRequest* httpRequest, long ownerUid);
	std::string deleteFile(std::string path);
};

