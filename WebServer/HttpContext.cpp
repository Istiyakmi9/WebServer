#include"HttpContext.h"
#include"Constants.h"
#include<map>
#include"LoginController.h"
#include <algorithm>
#include"DashboardController.h"

HttpContext::HttpContext(std::vector<char>* data, int dataLength) {
	_frontController = FrontController::InstanceOf();
	request = std::make_unique<HttpRequest>();
	response = std::make_unique<HttpResponse>();
	createHttpRequest(data, dataLength);
}

void HttpContext::createHttpRequest(std::vector<char>* data, int dataLen) {
	request->buildRequest(data, dataLen);
}

std::string HttpContext::getRequestType() {
	return request->getType();
}

std::string HttpContext::getHttpResponse(std::string responseMessage) {
	std::string contentType = "application/json";
	if (request->header->count("Content-Type") > 0) {
		auto result = request->header->find("Content-Type");
		//std::cout << "Content-type: " << result->second << std::endl;
		contentType = result->second;
	}
	std::map<std::string, std::string>* responseHeaser = new std::map<std::string, std::string>();
	responseHeaser->insert({ "Content-Type", contentType });
	responseHeaser->insert({ "access-control-allow-origin", "*" });
	return response->getHttpResponseString(Constants::Ok(), "{ \"responseBody\": " + responseMessage + " }", responseHeaser);
}

std::string HttpContext::getOptionsResponse() {
	std::string responseString = "";
	std::map<std::string, std::string>::iterator itr;
	for (itr = request->header->begin(); itr != request->header->end(); itr++) {
		responseString.append(itr->first);
	}
	return "";
}

std::string HttpContext::handleIncomingRequest() {
	std::string responseMessage = "";
	try {
		std::shared_ptr<std::map<std::string, std::string>> table(this->request->getRouteTable());
		/*
		*	Create controller mapping
		*	and call appropriate controller
		*	method using routetable
		*/

		std::string method = "";
		std::string controller = "";

		if (table.get()->count("method") > 0)
			method = table.get()->find("method")->second;

		if (table.get()->count("controller") > 0)
			controller = table.get()->find("controller")->second;

		if (method != "" && controller != "")
			responseMessage = _frontController->CallToController(controller, method, this->request->getBody());
	}
	catch (std::string ex) {
		std::cerr << "Error occured message: " << ex << std::endl;
	}

	if (responseMessage.find("{", 0) == std::string::npos) {
		if (responseMessage == "")
			responseMessage = "\"\"";
		else
			responseMessage = "\"" + responseMessage + "\"";
	}
	return getHttpResponse(responseMessage);
}