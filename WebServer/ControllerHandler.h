#pragma once

#include<iostream>
#include<map>

enum class ControllerMapping {
	Login = 1,
	Reports = 2,
	Dashboard = 3,
	Registration = 4,
	Master = 5
};

class ControllerHandler
{
private:
	std::map<std::string, ControllerMapping>* mapping;
	static ControllerHandler* instance;
	ControllerHandler() {
		mapping = new std::map<std::string, ControllerMapping>();
		mapping->insert({ "login", ControllerMapping::Login });
		mapping->insert({ "dashboard", ControllerMapping::Dashboard });
		mapping->insert({ "registration", ControllerMapping::Registration });
		mapping->insert({ "master", ControllerMapping::Master });
	}

public:
	// -------------  Singleton ApplicationCofig: Stopping copy constructor ----------- //
	ControllerHandler(const ControllerHandler&) = delete;

	~ControllerHandler() {
		delete instance;
		delete mapping;
	}

	// -------------  Singleton ApplicationCofig object should not be assignabled ----------- //
	void operator=(const ControllerHandler&) = delete;

	/*
		Static method to get only one instance of
		the object with thread safe approach
	*/
	static ControllerHandler* InstanceOf();

	std::string CallToController(std::string controller, std::string method, std::string requestBody);
};

