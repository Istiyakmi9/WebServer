
#pragma once

#include<iostream>

class FormDataContainer
{
private:
	std::string contentDisposition;
	std::string name;
	std::string filename;
	std::string fileContentType;
	long startIndex;
	long endIndex;

public:
	FormDataContainer();

	std::string getContentDisposition();
	void setContentDisposition(std::string value);

	std::string getFileContentType();
	void setFileContentType(std::string value);

	std::string getFilename();
	void setFilename(std::string value);

	std::string getName();
	void setName(std::string value);

	long getStartIndex();
	void setStartIndex(long value);

	long getEndIndex();
	void setEndIndex(long value);
};