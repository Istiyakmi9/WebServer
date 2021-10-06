#include "HttpRequest.h"
#include<sstream>
#include<string>
#include <algorithm> 
#include <locale>
#include"JsonManager.h"
#include<list>

HttpRequest::HttpRequest() {
	header = new std::map<std::string, std::string>();
	routeTable = std::make_shared<std::map<std::string, std::string>>();
}

bool HttpRequest::buildRouteMapping(std::string queryString) {
	bool flag = false;
	std::unique_ptr<std::list<std::string>> result = JsonManager::splitter(queryString, "\/");
	if (result.get()->size() > 0) {
		flag = true;
		std::string value = "";
		switch (result.get()->size()) {
		case 1:
			value = *(std::next(result.get()->begin(), 0));
			this->routeTable->insert({ "controller", value });
			break;
		case 2:
			value = *(std::next(result.get()->begin(), 0));
			this->routeTable->insert({ "controller", value });

			value = *(std::next(result.get()->begin(), 1));
			this->routeTable->insert({ "method", value });
			break;
		default:
			int i = 0;
			std::list<std::string>::iterator itr = result.get()->begin();
			while (itr != result.get()->end()) {
				if (i == 0)
					this->routeTable->insert({ "controller", *itr });
				else if (i == 1)
					this->routeTable->insert({ "method", *itr });
				else
					this->routeTable->insert({ "param" + std::to_string(i - 1), value });
				itr++;
				i++;
			}
			break;
		}
	}
	return flag;
}

HttpRequest::~HttpRequest() {
	delete header;
}

void HttpRequest::setType(std::string requestType) {
	this->type = requestType;
}

std::string HttpRequest::getType() {
	return this->type;
}

void HttpRequest::setBody(std::string body) {
	this->body = body;
}

std::string HttpRequest::getBody() {
	return this->body;
}

std::shared_ptr<std::map<std::string, std::string>> HttpRequest::getRouteTable() {
	return routeTable;
}

void HttpRequest::buildRequest(std::vector<char>* rawRequestData, int contentLength) {
	int i = 0;
	std::string bodyData = "";
	if (contentLength > 0) {
		bool carrierReturnFound = false;
		std::ostringstream lineStream;
		bool isFirstRead = true;
		bool isBodyAvailable = false;
		char ch = '\r';
		while (i < contentLength) {
			/*std::string key = "";
			std::string value = "";*/
			if (!isBodyAvailable) {
				lineStream.str("");
				lineStream.clear();
			}

			carrierReturnFound = false;
			ch = rawRequestData->at(i);
			while (ch != '\n' && i < contentLength) {
				/*if (ch == ':' && !isBodyAvailable) {
					key = lineStream.str();
					lineStream.str("");
					lineStream.clear();
					i++;
					continue;
				}*/
				lineStream << ch;
				i++;
				ch = rawRequestData->at(i);
			}

			if (lineStream.str() == "\r") carrierReturnFound = true;
			if (!isBodyAvailable) {
				std::unique_ptr <std::list<std::string>> result = JsonManager::firstSplitter(lineStream.str(), ": ");
				if (result->size() > 0) {
					if (isFirstRead) {
						std::unique_ptr <std::list<std::string>> result = JsonManager::splitter(lineStream.str(), " ");
						if (result.get()->size() != 3) {
							header->clear();
							break;
						}
						else {
							this->setType(*(std::next(result.get()->begin(), 0)));
							std::string routeMappringString = *(std::next(result.get()->begin(), 1));
							buildRouteMapping(routeMappringString);
							header->insert({ "HtmlType", *(std::next(result.get()->begin(), 2)) });
							isFirstRead = false;
						}
					}
					else {
						/*key = ;
						value = ;*/
						header->insert({ *(std::next(result.get()->begin(), 0)), *(std::next(result.get()->begin(), 1)) });
					}
				}
				else {
					if (ch == '\n' && carrierReturnFound)
						isBodyAvailable = true;
				}
			}
			//std::cout << key << ": " << lineStream.str() << std::endl;
			i++;
		}

		if (isBodyAvailable) {
			this->setBody(lineStream.str());
		}
	}
}