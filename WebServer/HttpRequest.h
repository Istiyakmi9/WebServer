#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<ApplicationConfig.h>
#include<fstream>
#include<sstream>

class HttpRequest
{
private:
	unsigned long i = 0;
	std::string body;
	void setBody(std::string);
	void setType(std::string);
	std::shared_ptr<std::map<std::string, std::string>> routeTable;
	void readHeaderContent(std::vector<char>*, int);
	void readJsonBody(std::vector<char>*, int);
	void readFormBody(std::vector<char>*, int, std::string);
	std::stringstream readLine(std::vector<char>*, int);
	std::string readFileData(std::vector<char>*, int, std::string);
	std::vector<char>* rawFormData = nullptr;

	int contentIndexPosition = 0;
	unsigned long contentLength = 0;
	std::string delimiter;
	bool isFormData;
public:
	explicit HttpRequest();
	~HttpRequest();
	
	std::string type;
	ApplicationConfig* config = nullptr;
	std::map<std::string, std::string>* header;
	void buildRequest(std::vector<char>*, int contentLength);
	std::string getBody();
	bool buildRouteMapping(std::string);
	std::shared_ptr<std::map<std::string, std::string>> getRouteTable();
	std::map<std::string, std::string>* convertToMap(std::string sourceString);
};

