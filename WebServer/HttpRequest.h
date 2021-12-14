#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<ApplicationConfig.h>
#include<fstream>
#include<sstream>
#include"FormDataContainer.h"

class HttpRequest
{
private:
	long i = 0;
	bool isQueryString = false;
	std::string body;
	void setBody(std::string);
	void setType(std::string);
	std::map<std::string, std::string>* routeTable;
	void readHeaderContent();
	void readJsonBody();
	void readFormBody();
	std::stringstream readBodyNextLine();
	std::string readFileData(FormDataContainer*);

	char* rawRequestData = nullptr;
	std::map<std::string, FormDataContainer*>* formDataContainerMap = nullptr;
	bool buildRouteMapping(std::string);
	FormDataContainer* convertToMap(std::string sourceString);

	ApplicationConfig* config = nullptr;
	int contentIndexPosition = 0;
	long contentLength = 0;
	std::string delimiter;
	bool isFormData;
public:
	explicit HttpRequest();
	~HttpRequest();
	
	std::string type;
	std::map<std::string, std::string>* header;
	std::string getBody();
	void buildRequest(char*, int contentLength);
	std::map<std::string, std::string>* getRouteTable();
	std::string getFormJsonData(std::string);
	char* getFormFileData(std::string);
	bool saveFormFile(std::string searchName, std::string fileName, std::string path = "", bool isRelativePath = true);
	std::map<std::string, FormDataContainer*>* getFromDataContainer();
	char* getHttpRequestRawData();
	int requestedType = 1;
	std::string staticFilePath = "";
	int requestMethodId = 1;
};

