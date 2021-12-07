#pragma once

#include<functional>
#include<iostream>
#include<map>
#include"HttpRequest.h"
#include"HttpContext.h"

using std::placeholders::_1;
using std::bind;

template<class T>
class BaseController
{
private:
	typedef std::function<std::string(std::string arg0)> Function;
	std::map<std::string, Function>* fn;

public:
	BaseController() {
		fn = new std::map<std::string, Function>();
	}

	~BaseController() {
		delete fn;
	}

	HttpRequest* httpRequest = nullptr;
	HttpContext* httpContext = nullptr;
	std::string RequestGateway(std::string method, HttpContext* _httpContext) {
		std::string response = "";
		httpContext = _httpContext;
		httpRequest = _httpContext->getHttpRequest();

		if (fn->count(method) > 0) {
			Function fnptr = fn->find(method)->second;
			response = fnptr(httpRequest->getBody());
		}
		return response;
	}

	void add(std::string name, Function pointer) {
		if (fn->count(name) <= 0)
			fn->insert({ name, pointer });
	}
};