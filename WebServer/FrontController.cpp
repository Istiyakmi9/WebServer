#include "FrontController.h"
#include"LoginController.h"
#include"MasterController.h"
#include"ItemAndGoodsController.h"

#include <algorithm>
#include"DashboardController.h"
#include<mutex>
#include"Util.h"

std::mutex mtx;

FrontController* FrontController::instance = nullptr;

FrontController* FrontController::InstanceOf() {
	if (instance == nullptr) {
		std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
		mtx.lock(); {
			try {
				instance = new FrontController();
			}
			catch (int err) {
				mtx.unlock();
				return nullptr;
			}
		}
		mtx.unlock();
	}
	return FrontController::instance;
}

std::string FrontController::CallToController(std::string controller, std::string method, std::string requestBody) {
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

		case ControllerMapping::ItemAndGoods: {
			ItemAndGoodsController* item = nullptr;
			try {
				item = new ItemAndGoodsController();
				responseMessage = item->RequestGateway(method, requestBody);
				delete item;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				delete item;
			}
		}
											break;
		default:
			break;
		}
	}

	return responseMessage;
}