#pragma once
#include<iostream>
#include"HttpRequest.h"
#include"DbUtility.h"
#include<FileDetail.h>

class FileManager
{
private:
	DbUtility* dbUtility;

public:
	FileManager();
	~FileManager();
	void saveHttpRequestedFile(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest);
	void saveHttpRequestedFile_Unix(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest);
	std::string saveFile(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest);
	std::string deleteFile(std::string path);
	bool insertRecord(FileDetail* fileDetail);
	bool updateRecord(FileDetail* fileDetail);
};