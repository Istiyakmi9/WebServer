#pragma once

#include<iostream>
#include<winsock2.h>
#include<sstream>
#include<list>
#include"JsonManager.h"
#include"FrontController.h"
#include<list>

class ManageSocket
{
private:
	FrontController* frontController;
	void GetSenderDetail(sockaddr_in client);

public:
	explicit ManageSocket();
	int createSocket();
	void bindSocket();
	void listenClients();
	const std::list<std::string> acceptedStaticFileTypes = { "jpg", "png", "jpeg" };
};

