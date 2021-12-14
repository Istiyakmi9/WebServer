#include"HttpContext.h"
#include"Constants.h"
#include<map>
#include <algorithm>
#include<exception>
#include <fstream>

HttpContext::HttpContext(char* data, int dataLength) {
	request = new HttpRequest();
	response = new HttpResponse();
	createHttpRequest(data, dataLength);
}

void HttpContext::createHttpRequest(char* data, int dataLen) {
	request->buildRequest(data, dataLen);
}

HttpRequest* HttpContext::getHttpRequest() {
	return request;
}

std::string HttpContext::getRequestType() {
	return request->type;
}

std::string HttpContext::getHttpResponseForStaticFile(std::string filePath, unsigned long long& FileSize) {
	std::string filedata = "";
	WIN32_FIND_DATA findFileData;
	HANDLE handle = FindFirstFile(filePath.c_str(), &findFileData);
	int found = handle != INVALID_HANDLE_VALUE;
	std::string responseBody = "";
	if (found) {
		FileSize = findFileData.nFileSizeHigh;
		FileSize <<= sizeof(findFileData.nFileSizeHigh) * 8;
		FileSize |= findFileData.nFileSizeLow;
		if (FileSize > 0) {
			std::cout << FileSize;
		}

		OVERLAPPED ol = { 0 };
		HANDLE fileHandler = CreateFile(
			filePath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		imageBuffer = new char[FileSize];
		memset(imageBuffer, '\0', FileSize);
		DWORD dwBytes = 0;
		bool flag = ReadFileEx(fileHandler, imageBuffer, FileSize, &ol, 0);
		FindClose(handle);
		responseBody = response->getHttpResponseStaticFile(Constants::Ok(), imageBuffer, FileSize, "image/jpeg");
	}
	else {
		FileSize = 0;
		responseBody = response->getHttpResponseStaticFile(Constants::PageNotFount(), "", FileSize, "image/jpeg");
	}

	return responseBody;
}

std::string HttpContext::getHttpResponse(std::string responseMessage) {
	std::string contentType = "application/json";
	if (request->header->count("Content-Type") > 0) {
		auto result = request->header->find("Content-Type");
		contentType = result->second;
	}
	std::map<std::string, std::string>* responseHeader = new std::map<std::string, std::string>();
	responseHeader->insert({ "Content-Type", contentType });
	responseHeader->insert({ "access-control-allow-origin", "*" });
	std::string responseContent = response->getHttpResponseString(Constants::Ok(), "{ \"responseBody\": " + responseMessage + " }", responseHeader);
	delete responseHeader;
	return responseContent;
}

std::string HttpContext::getOptionsResponse() {
	std::string responseString = "";
	std::map<std::string, std::string>::iterator itr;
	for (itr = request->header->begin(); itr != request->header->end(); itr++) {
		responseString.append(itr->first);
	}
	return "";
}