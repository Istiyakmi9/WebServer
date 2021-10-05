#pragma once

#include<windows.h>
#include<vector>
#include"HttpRequest.h"
#include"HttpResponse.h"

class HttpContext
{
private:
	std::unique_ptr<HttpRequest> request = nullptr;
	std::unique_ptr<HttpResponse> response = nullptr;
	void createHttpRequest(std::vector<char>*, int);
	std::map<std::string, int>* mapping;

public:
	explicit HttpContext(std::vector<char>*, int);
	~HttpContext() {
		delete mapping;
	}
	std::string getHttpResponse(std::string responseMessage);
	std::string getRequestType();
	std::string handleIncomingRequest();
	std::string getOptionsResponse();
	void addController();
};

