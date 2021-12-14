#pragma once

#include<iostream>
#include<windows.h>
#include<vector>
#include"HttpRequest.h"
#include"HttpResponse.h"
#include<string>

class HttpContext
{
private:
	HttpRequest* request = nullptr;
	HttpResponse* response = nullptr;
	void createHttpRequest(char*, int);
	std::string controllerName;
	std::string methodName;
	char* imageBuffer = nullptr;

public:
	explicit HttpContext(char*, int);
	~HttpContext() {
		//delete imageBuffer;
		delete request;
		delete response;
	}

	std::string getHttpResponse(std::string responseMessage);
	std::string getHttpResponseForStaticFile(std::string filePath, unsigned long long& size);
	std::string getRequestType();
	std::string getOptionsResponse();
	HttpRequest* getHttpRequest();
};