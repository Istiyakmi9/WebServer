#pragma once

#include<windows.h>
#include<vector>
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"FrontController.h"

class HttpContext
{
private:
	std::unique_ptr<HttpRequest> request = nullptr;
	std::unique_ptr<HttpResponse> response = nullptr;
	void createHttpRequest(std::vector<char>*, int);
	FrontController* _frontController;

public:
	explicit HttpContext(std::vector<char>*, int);

	std::string getHttpResponse(std::string responseMessage);
	std::string getRequestType();
	std::string handleIncomingRequest();
	std::string getOptionsResponse();
};

