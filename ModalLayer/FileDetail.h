
#pragma once


#ifdef FILEDETAIL_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>
#include<map>
#include"JsonManager.h"
/*--------- Method names enum -----------*/

enum class FileDetailFuncNames {
	setExtension, setFileDetailId, setFileName, setFileOwnerId, setFilePath
};

class DECLSPEC FileDetail
{
private:
	long FileDetailId;
	std::string FileName;
	std::string FilePath;
	std::string Extension;
	long FileOwnerId;

public:
	FileDetail() {
		this->FileDetailId = 0;
		this->FileOwnerId = 0;
	}

	std::string getExtension();
	void setExtension(std::string value);

	long getFileDetailId();
	void setFileDetailId(long value);

	std::string getFileName();
	void setFileName(std::string value);

	long getFileOwnerId();
	void setFileOwnerId(long value);

	std::string getFilePath();
	void setFilePath(std::string value);

	void setPrivateFieldsValue(std::string);
};