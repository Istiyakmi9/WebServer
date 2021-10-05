#pragma once

#include<iostream>
#include"Constants.h"
#include<map>

class HttpResponse
{
public:
	HttpResponse();
	std::string getHttpResponseString(int flag, std::string responseData, std::map<std::string, std::string> *customHeaders);
};

