#include "HttpRequest.h"
#include<string>
#include <algorithm> 
#include <locale>
#include"JsonManager.h"
#include<list>
#include<windows.h>

HttpRequest::HttpRequest() {
	config = ApplicationConfig::getInstance();
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
	if (rawFormData != nullptr)
		delete rawFormData;
}

void HttpRequest::setType(std::string requestType) {
	this->type = requestType;
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

void HttpRequest::readHeaderContent(std::vector<char>* rawRequestData, int contentLength) {
	std::ostringstream lineStream;
	bool isFirstRead = true;
	char ch = '\r';
	while (i < contentLength) {
		lineStream.str("");
		lineStream.clear();

		ch = rawRequestData->at(i);
		while (ch != '\n' && i < contentLength) {
			lineStream << ch;
			i++;
			ch = rawRequestData->at(i);
		}

		if (lineStream.str() == "\r" && ch == '\n') {
			i++;
			break;
		}
		else {
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
					header->insert({ *(std::next(result.get()->begin(), 0)), *(std::next(result.get()->begin(), 1)) });
				}
			}
		}
		//std::cout << key << ": " << lineStream.str() << std::endl;
		i++;
	}
}

std::stringstream HttpRequest::readLine(std::vector<char>* request, int length) {
	std::stringstream ss;
	char ch = 0;
	int index = 0;
	while (i < length) {
		ch = request->at(i);
		if (ch == '\n') {
			i++;
			break;
		}

		if (ch != '\r')
			ss << ch;
		i++;
		index++;
	}
	return ss;
}

std::string HttpRequest::readFileData(std::vector<char>* request, int length, std::string _delimiter) {
	std::ostringstream message;
	char ch;
	DWORD size = 0;
	try {
		const char* fileName = "file.jpg";

		HANDLE file = CreateFile(fileName,    // name of the file
			GENERIC_WRITE, // open for writing
			0,             // sharing mode, none in this case
			0,             // use default security descriptor
			CREATE_ALWAYS, // overwrite if exists
			FILE_ATTRIBUTE_NORMAL,
			0
		);

		std::ostringstream fileStream;
		unsigned char* bytes = new unsigned char[10000];
		if (file) {
			i = i + 2;
			while (i < length) {
				memset(bytes, '\0', 10000);
				while (i < length) {
					ch = request->at(i);
					bytes[size] = ch;
					i++;
					size++;
				}

				WriteFile(file, bytes, size, &size, NULL);
				i++;
			}
			CloseHandle(file);
		}
		else {
			std::cerr << "CreateFile() failed:" << GetLastError() << "\n";
		}

	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return "";
}

std::map<std::string, std::string>* HttpRequest::convertToMap(std::string sourceString) {
	std::map<std::string, std::string>* result = new std::map<std::string, std::string>();
	auto items = Util::splitter(sourceString, ";");

	std::string key;
	std::string value;
	size_t pos = 0;
	std::string delimiter = ": ";
	auto ptr = items->begin();
	while (ptr != items->end()) {
		if ((pos = ptr->find(delimiter)) != std::string::npos) {
			key = ptr->substr(0, pos);
			key = Util::replace_all(key, "\"", "");
			ptr->erase(0, pos + delimiter.length());
		}

		delimiter = "=";
		value = Util::replace_all(*ptr, "\"", "");
		result->insert({ key, value });
		ptr++;
	}

	items.release();
	return result;
}

void HttpRequest::readFormBody(std::vector<char>* rawRequestData, int contentLength, std::string _delimiter) {
	char ch = '\0';
	int size = 0;
	this->contentIndexPosition = i;
	std::stringstream ss;
	ss = readLine(rawRequestData, contentLength);

	if (ss.str().find(_delimiter) >= 0) {
		this->delimiter = _delimiter;
		if (header->count("Content-Length") > 0) {
			this->contentLength = atol((header->find("Content-Length")->second).c_str());
		}

		while (i < contentLength) {
			ss.clear();
			ss = readLine(rawRequestData, contentLength);
			auto items = convertToMap(ss.str());

			//readFileData(rawRequestData, contentLength, _delimiter);

			delete items;
		}
	}

	this->setBody("");
}

void HttpRequest::readJsonBody(std::vector<char>* rawRequestData, int contentLength) {
	std::ostringstream lineStream;
	bool isFirstRead = true;
	char ch = '\r';
	while (i < contentLength) {
		ch = rawRequestData->at(i);
		if (ch != '\n')
			lineStream << ch;
		i++;
	}

	this->setBody(lineStream.str());
}

void HttpRequest::buildRequest(std::vector<char>* rawRequestData, int contentLength) {
	this->i = 0;
	std::string bodyData = "";
	if (contentLength > 0) {
		bool carrierReturnFound = false;
		std::ostringstream lineStream;
		bool isFirstRead = true;
		bool isBodyAvailable = false;
		char ch = '\r';
		std::string contentType = "";

		//--------------- Reading header content ----------------//
		readHeaderContent(rawRequestData, contentLength);

		if (header->count("Content-Type") > 0) {
			contentType = header->find("Content-Type")->second;
			int type = config->findHeader(contentType);
			switch (type) {
			case 1: {
				/*--------------------------------  Request content is application/json format -------------------------------*/
				readJsonBody(rawRequestData, contentLength);
			}
				  break;

			case 2: {
				/*--------------------------------  Request content is form-data format  --------------------------------------------*/
				auto formData = JsonManager::splitter(contentType, "boundary=");
				auto it = std::next(formData->begin(), 1);
				rawFormData = rawRequestData;
				readFormBody(rawRequestData, contentLength, *it);
			}
				  break;
			default: {
				this->setBody("");
			}
				   break;
			}
		}
	}
}