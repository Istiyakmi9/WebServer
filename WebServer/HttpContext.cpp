#include"HttpContext.h"
#include"Constants.h"
#include<map>
#include"LoginController.h"
#include <algorithm>
#include"DashboardController.h"

HttpContext::HttpContext(std::vector<char>* data, int dataLength) {
	mapping = new std::map<std::string, int>();
	addController();
	request = std::make_unique<HttpRequest>();
	response = std::make_unique<HttpResponse>();
	createHttpRequest(data, dataLength);
}

enum ControllerMapping {
	Login = 1,
	Reports = 2,
	Dashboard = 3
};

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

		std::string method = table.get()->find("method")->second;
		std::string controller = table.get()->find("controller")->second;


		//std::string controllerName = "";
		//std::transform(controller.begin(),
		//	controller.end(),
		//	controllerName.begin(),
		//	::tolower);

		auto maptype = mapping->find(controller);
		int controllerId = maptype->second;

		switch (controllerId) {
		case Login: {
			LoginController* loginController = nullptr;
			try {
				loginController = new LoginController();
				if (method == "")
					method = request->getType();
				responseMessage = loginController->RequestGateway(method, request->getBody());
				delete loginController;
			}
			catch (int e) {
				delete loginController;
			}
		}
				  break;
		case Reports:
			break;
		case Dashboard: {
			DashboardController* dashboard = nullptr;
			try {
				dashboard = new DashboardController();
				if (method == "")
					method = request->getType();
				responseMessage = dashboard->RequestGateway(method, request->getBody());
				delete dashboard;
			}
			catch (int e) {
				delete dashboard;
			}
		}
					  break;
		}
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

void HttpContext::addController() {
	mapping->insert({ "login", Login });
	mapping->insert({ "dashboard", Dashboard });
}