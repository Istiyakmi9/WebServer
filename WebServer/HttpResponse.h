#pragma once

#include<iostream>
#include"Constants.h"
#include<map>

class HttpResponse
{
public:
	HttpResponse();
	std::string getHttpResponseString(int flag, std::string responseData, std::map<std::string, std::string>* customHeaders);
	std::string getHttpResponseStaticFile(int flag, const char* imageBuffer, unsigned long long& size, std::string mimeType);
};

