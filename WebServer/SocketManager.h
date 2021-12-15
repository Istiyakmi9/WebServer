#pragma once

#include<iostream>
#include<winsock2.h>
#include<sstream>
#include<list>
#include"JsonManager.h"
#include"FrontController.h"
#include<list>

class SocketManager
{
private:
	FrontController* frontController;
	void GetSenderDetail(sockaddr_in client);

public:
	explicit SocketManager();
	int createSocket();
	void bindSocket();
	void listenClients();
	const std::list<std::string> acceptedStaticFileTypes = { "jpg", "png", "jpeg" };
};

