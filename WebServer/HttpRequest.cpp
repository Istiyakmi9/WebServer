#include"HttpRequest.h"
#include<string>
#include <algorithm> 
#include <locale>
#include"JsonManager.h"
#include<list>
#include<windows.h>

HttpRequest::HttpRequest() {
	config = ApplicationConfig::getInstance();
	header = new std::map<std::string, std::string>();
	routeTable = new std::map<std::string, std::string>();
}

bool HttpRequest::buildRouteMapping(std::string queryString) {
	bool flag = false;
	std::unique_ptr<std::list<std::string>> arguments = JsonManager::splitter(queryString, "?");
	std::string data = *(std::next(arguments.get()->begin(), 0));
	std::unique_ptr<std::list<std::string>> routes = JsonManager::splitter(data, "\/");
	if (routes.get()->size() > 0) {
		flag = true;
		std::string value = "";
		switch (routes.get()->size()) {
		case 1:
			value = *(std::next(routes.get()->begin(), 0));
			this->routeTable->insert({ "controller", value });
			break;
		case 2:
			value = *(std::next(routes.get()->begin(), 0));
			this->routeTable->insert({ "controller", value });

			value = *(std::next(routes.get()->begin(), 1));
			this->routeTable->insert({ "method", value });
			break;
		default:
			int i = 1;
			std::list<std::string>::iterator itr = routes.get()->begin();
			while (itr != routes.get()->end()) {
				switch (i) {
				case 1:
					this->routeTable->insert({ "controller", *itr });
					break;
				case 2:
					this->routeTable->insert({ "method", *itr });
					break;
				default:
					this->routeTable->insert({ "route_" + std::to_string(i - 2), *itr });
					break;
				}
				itr++;
				i++;
			}
			break;
		}

		if (arguments->size() == 2) {
			std::string queryString = *(std::next(arguments.get()->begin(), 1));
			this->routeTable->insert({ "queryString", queryString });
			this->isQueryString = true;
		}
	}
	return flag;
}

HttpRequest::~HttpRequest() {
	delete header;
	if (formDataContainerMap != nullptr)
		Util::clean_map<std::string, FormDataContainer*>(formDataContainerMap);

	if (routeTable != nullptr)
		delete routeTable;
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

std::map<std::string, std::string>* HttpRequest::getRouteTable() {
	return routeTable;
}

void HttpRequest::readHeaderContent() {
	std::ostringstream lineStream;
	bool isFirstRead = true;
	char ch = '\r';
	while (i < contentLength) {
		lineStream.str("");
		lineStream.clear();

		ch = rawRequestData[i];
		while (ch != '\n' && i < contentLength) {
			lineStream << ch;
			i++;
			ch = rawRequestData[i];
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
						if (routeMappringString.find(".") == -1) {
							buildRouteMapping(routeMappringString);
							header->insert({ "HtmlType", *(std::next(result.get()->begin(), 2)) });
							isFirstRead = false;
						}
						else {
							auto value = Util::splitter(routeMappringString, ".");
							if (value->size() > 1) {
								this->requestedType = 2;
								this->staticFilePath = routeMappringString;
								break;
							}
						}
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

std::stringstream HttpRequest::readBodyNextLine() {
	std::stringstream ss;
	char ch = 0;
	int index = 0;
	while (i < this->contentLength) {
		ch = rawRequestData[i];
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

std::string HttpRequest::readFileData(FormDataContainer* item) {
	std::ostringstream message;
	unsigned char ch = '\0';
	unsigned endPosition = 0;
	long long value = 0;
	bool found = false;
	try {
		int delimiterLen = 72;
		while (i < contentLength) {
			ch = this->rawRequestData[i];
			if (ch == '-') {
				endPosition = i - 1;
				i++;
				message.str("");
				int delimiterIndex = 0;
				message << ch;
				while (i < contentLength) {
					ch = rawRequestData[i];
					if (delimiterIndex < delimiterLen && ch != '\n') {
						if (ch != '\r')
							message << ch;
					}
					else {
						value = message.str().find(this->delimiter);
						if (value >= 0) {
							item->setEndIndex(endPosition);
							found = true;
						}
						i++;
						break;
					}
					i++;
					delimiterIndex++;
				}

				if (found)
					break;
			}
			i++;
		}
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return "";
}

FormDataContainer* HttpRequest::convertToMap(std::string sourceString) {
	FormDataContainer* formDataContainer = new FormDataContainer();
	std::string content = "";
	do {
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

			if (key == "Content-Disposition")
				formDataContainer->setContentDisposition(value);
			else if (key == "name")
				formDataContainer->setName(value);
			else if (key == "filename")
				formDataContainer->setFilename(value);
			else if (key == "Content-Type")
				formDataContainer->setFileContentType(value);

			ptr++;
		}

		items.release();
		sourceString = readBodyNextLine().str();
		if (sourceString == "")
			break;
	} while (i < contentLength);
	return formDataContainer;
}

void HttpRequest::readFormBody() {
	char ch = '\0';
	int size = 0;
	this->contentIndexPosition = i;
	std::stringstream ss;
	std::string contentTypeValue = "";
	ss = readBodyNextLine();

	if (ss.str().find(delimiter) >= 0) {
		if (header->count("Content-Length") > 0) {
			this->contentLength = atol((header->find("Content-Length")->second).c_str()) + i - (delimiter.length() + 4);
		}

		while (i < contentLength) {
			ss.clear();
			ss = readBodyNextLine();
			if (ss.str() != "") {
				auto item = convertToMap(ss.str());
				item->setStartIndex(i);
				readFileData(item);

				formDataContainerMap->insert({ item->getName(), item });
			}
		}
	}

	this->setBody("");
}

void HttpRequest::readJsonBody() {
	std::ostringstream lineStream;
	bool isFirstRead = true;
	char ch = '\r';
	while (i < contentLength) {
		ch = rawRequestData[i];
		if (ch != '\n')
			lineStream << ch;
		i++;
	}

	this->setBody(lineStream.str());
}

void HttpRequest::buildRequest(char* data, int length) {
	this->i = 0;
	this->rawRequestData = data;
	this->contentLength = length;
	std::string bodyData = "";
	if (contentLength > 0) {
		bool carrierReturnFound = false;
		std::ostringstream lineStream;
		bool isFirstRead = true;
		bool isBodyAvailable = false;
		char ch = '\r';
		std::string contentType = "";

		//--------------- Reading header content ----------------//
		readHeaderContent();

		//switch (this->requestMethodId) {
		//case (int)ApplicationConfig::RequestMethodType::GET:
		//	break;
		//case (int)ApplicationConfig::RequestMethodType::POST:
		//	break;
		//case (int)ApplicationConfig::RequestMethodType::PUT:
		//	break;
		//case (int)ApplicationConfig::RequestMethodType::FETCH:
		//	break;
		//default:
		//	break;
		//}

		if (this->requestedType == 1) {
			if (this->type == "GET") {
				if (this->isQueryString) {
					std::stringstream ss;
					ss << "{";
					std::string arguments = this->routeTable->find("queryString")->second;
					auto params = Util::splitter(arguments, "&");
					std::string multi = "";
					for (auto ptr = params->begin(); ptr != params->end(); ptr++) {
						auto data = Util::splitter(arguments, "=");
						ss << multi + "\"" + *(std::next(data.get()->begin(), 0)) + "\":";
						ss << "\"" + *(std::next(data.get()->begin(), 1)) + "\"";
						multi = ", ";
						data.release();
					}

					params.release();
					ss << "}";
					this->setBody(ss.str());
				}
			}
			else {
				if (header->count("Content-Type") > 0) {
					contentType = header->find("Content-Type")->second;
					int type = config->findHeader(contentType);
					switch (type) {
					case 1: {
						/*--------------------------------  Request content is application/json format -------------------------------*/
						readJsonBody();
					}
						  break;

					case 2: {
						/*--------------------------------  Request content is form-data format  --------------------------------------------*/
						auto formData = JsonManager::splitter(contentType, "boundary=");
						auto it = std::next(formData->begin(), 1);
						formDataContainerMap = new std::map<std::string, FormDataContainer*>();
						this->delimiter = *it;
						readFormBody();
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
	}
}

std::string HttpRequest::getFormJsonData(std::string name) {
	std::stringstream stream;
	if (formDataContainerMap->count(name) > 0) {
		FormDataContainer* formDataContainer = formDataContainerMap->find(name)->second;
		int i = formDataContainer->getStartIndex();
		int lastIndex = formDataContainer->getEndIndex();
		while (i < lastIndex) {
			stream << rawRequestData[i];
			i++;
		}
	}
	return stream.str();
}

char* HttpRequest::getFormFileData(std::string name) {
	return nullptr;
}

bool HttpRequest::saveFormFile(std::string searchName, std::string fileName, std::string path, bool isRelativePath) {
	std::string location = "";
	if (formDataContainerMap->count(searchName) > 0) {
		FormDataContainer* filePtr = formDataContainerMap->find(searchName)->second;
		if (isRelativePath) {
			ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
			if (path != "") {
				location = Util::combine(applicationConfig->getApplicationWorkingDirectory(), path);

				if (CreateDirectory(location.c_str(), NULL)) {
					//------------- Directory created -----------------
					std::cout << "Folder create successfully" << std::endl;
				}
				else {
					//------------- Directory already exists -----------------
					std::cout << "Folder already exists" << std::endl;
				}
			}
			else {
				location = applicationConfig->getApplicationWorkingDirectory();
			}

			std::string filePath = Util::combine(location, fileName);
			WIN32_FIND_DATA findFileData;
			HANDLE handle = FindFirstFile(filePath.c_str(), &findFileData);
			int found = handle != INVALID_HANDLE_VALUE;
			HANDLE fileHandler = NULL;
			if (found) {
				DeleteFile(filePath.c_str());
			}

			fileHandler = CreateFile(
				filePath.c_str(),
				GENERIC_WRITE,
				0,
				0,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				0
			);

			if (fileHandler) {
				std::cout << "File create successfully" << std::endl;
				long index = filePtr->getStartIndex();
				long endIndex = filePtr->getEndIndex();
				DWORD dwBytes = 0;
				while (index < endIndex) {
					WriteFile(
						fileHandler,
						&rawRequestData[index],
						1,
						&dwBytes,
						NULL
					);

					index++;
				}
				CloseHandle(fileHandler);
			}
			else {
				std::cout << "Fail to create file" << std::endl;
				return false;
			}
		}
		else {

		}
	}
	else {
		std::cerr << "No entry found with the name [" + fileName + "] in request form-data body." << std::endl;
	}
#ifdef  _WIN32

#elif __linux__

#endif //  _WIN32
	return true;
}

std::map<std::string, FormDataContainer*>* HttpRequest::getFromDataContainer() {
	return this->formDataContainerMap;
}

char* HttpRequest::getHttpRequestRawData() {
	return this->rawRequestData;
}