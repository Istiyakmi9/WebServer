#pragma once

#include<functional>
#include<iostream>
#include<map>

using std::placeholders::_1;
using std::bind;

template<class T>
class BaseController
{
private:
	typedef std::function<std::string (std::string arg0)> Function;
	std::map<std::string, Function>* fn;

public:
	BaseController() {
		fn = new std::map<std::string, Function>();
	}

	~BaseController() {
		delete fn;
	}

	std::string RequestGateway(std::string method, std::string argument) {
		std::string response = "";
		if (fn->count(method) > 0) {
			Function fnptr = fn->find(method)->second;
			response = fnptr(argument);
		}
		return response;
	}

	void add(std::string name, Function pointer) {
		if(fn->count(name) <= 0)
		fn->insert({ name, pointer });
	}
};