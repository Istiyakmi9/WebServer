#include"FrontController.h"

#include"DashboardController.h"
#include"ReportsController.h"
#include"ItemAndGoodsController.h"
#include"RegistrationController.h"
#include"MasterController.h"
#include"LoginController.h"

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

std::string FrontController::CallToController(HttpContext* httpContext) {
	std::string responseMessage = "";
	std::string method = "";
	std::string controller = "";

	std::map<std::string, std::string>* table = httpContext->getHttpRequest()->getRouteTable();
	/*
	*	Create controller mapping
	*	and call appropriate controller
	*	method using routetable
	*/

	if (table->count("method") > 0)
		method = table->find("method")->second;

	if (table->count("controller") > 0)
		controller = table->find("controller")->second;


	if (this->mapping->count(controller) > 0) {
		ControllerMapping _controllerMapping = this->mapping->find(controller)->second;

		switch (_controllerMapping)
		{
		case ControllerMapping::Login: {
			LoginController* loginController = nullptr;
			try {
				loginController = new LoginController();
				responseMessage = loginController->RequestGateway(method, httpContext);
				delete loginController;
			}
			catch (int e) {
				delete loginController;
			}
		}
									 break;
		case ControllerMapping::Registration: {
			RegistrationController* registration = nullptr;
			try {
				registration = new RegistrationController();
				responseMessage = registration->RequestGateway(method, httpContext);
				delete registration;
			}
			catch (std::exception& e) {
				delete registration;
				std::cerr << e.what();
			}
		}
											break;
		case ControllerMapping::Dashboard: {
			DashboardController* dashboard = nullptr;
			try {
				dashboard = new DashboardController();
				responseMessage = dashboard->RequestGateway(method, httpContext);
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
				responseMessage = master->RequestGateway(method, httpContext);
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
				responseMessage = item->RequestGateway(method, httpContext);
				delete item;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				delete item;
			}
		}
											break;

		case ControllerMapping::Reports: {
			ReportsController* item = nullptr;
			try {
				item = new ReportsController();
				responseMessage = item->RequestGateway(method, httpContext);
				delete item;
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				delete item;
			}
		}
		default:
			break;
		}
	}

	return responseMessage;
}