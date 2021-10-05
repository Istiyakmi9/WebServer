#pragma once

#include<iostream>
#include<map>
#include<vector>

class HttpRequest
{
private:
	std::string type;
	std::string body;
	void setBody(std::string);
	void setType(std::string);
	std::shared_ptr<std::map<std::string, std::string>> routeTable;

public:
	explicit HttpRequest();
	~HttpRequest();
	std::map<std::string, std::string>* header;
	void buildRequest(std::vector<char>*, int contentLength);
	std::string getType();
	std::string getBody();
	bool buildRouteMapping(std::string);
	std::shared_ptr<std::map<std::string, std::string>> getRouteTable();
};

