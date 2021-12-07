#include"HttpContext.h"
#include"Constants.h"
#include<map>
#include"LoginController.h"
#include <algorithm>
#include"DashboardController.h"

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

std::string HttpContext::getHttpResponse(std::string responseMessage) {
	std::string contentType = "application/json";
	if (request->header->count("Content-Type") > 0) {
		auto result = request->header->find("Content-Type");
		//std::cout << "Content-type: " << result->second << std::endl;
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