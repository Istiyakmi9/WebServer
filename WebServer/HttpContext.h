#pragma once

#include<windows.h>
#include<vector>
#include"HttpRequest.h"
#include"HttpResponse.h"

class HttpContext
{
private:
	HttpRequest* request = nullptr;
	HttpResponse* response = nullptr;
	void createHttpRequest(char*, int);
	std::string controllerName;
	std::string methodName;

public:
	explicit HttpContext(char*, int);
	~HttpContext() {
		delete request;
		delete response;
	}

	std::string getHttpResponse(std::string responseMessage);
	std::string getRequestType();
	std::string getOptionsResponse();
	HttpRequest* getHttpRequest();
};