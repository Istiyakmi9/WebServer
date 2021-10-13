#include "ControllerHandler.h"
#include"LoginController.h"
#include"MasterController.h"

#include <algorithm>
#include"DashboardController.h"
#include<mutex>

std::mutex mtx;

ControllerHandler* ControllerHandler::instance = nullptr;

ControllerHandler* ControllerHandler::InstanceOf() {
	if (instance == nullptr) {
		std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
		mtx.lock(); {
			try {
				instance = new ControllerHandler();
			}
			catch (int err) {
				mtx.unlock();
				return nullptr;
			}
		}
		mtx.unlock();
	}
	return ControllerHandler::instance;
}

std::string ControllerHandler::CallToController(std::string controller, std::string method, std::string requestBody) {
	std::string responseMessage = "";
	if (this->mapping->count(controller) > 0) {
		ControllerMapping _controllerMapping = this->mapping->find(controller)->second;

		switch (_controllerMapping)
		{
		case ControllerMapping::Login: {
			LoginController* loginController = nullptr;
			try {
				loginController = new LoginController();
				responseMessage = loginController->RequestGateway(method, requestBody);
				delete loginController;
			}
			catch (int e) {
				delete loginController;
			}
		}
									 break;
		case ControllerMapping::Reports:
			break;
		case ControllerMapping::Registration: {

		}
											break;
		case ControllerMapping::Dashboard: {
			DashboardController* dashboard = nullptr;
			try {
				dashboard = new DashboardController();
				responseMessage = dashboard->RequestGateway(method, requestBody);
				delete dashboard;
			}
			catch (int e) {
				delete dashboard;
			}
		}
										 break;

		case ControllerMapping::Master: {
			MasterController* master = nullptr;
			try {
				master = new MasterController();
				responseMessage = master->RequestGateway(method, requestBody);
				delete master;
			}
			catch (int e) {
				delete master;
			}
		}
										 break;
		default:
			break;
		}
	}

	return responseMessage;
}