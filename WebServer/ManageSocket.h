#pragma once

#include<iostream>
#include<winsock2.h>
#include<sstream>
#include<list>
#include"JsonManager.h"

class ManageSocket
{
private:
	int ReceivedChunkSize = 512;
	int SendChunkSize = 4 * 1024;
	void GetSenderDetail(sockaddr_in client);

public:
	explicit ManageSocket();
	int createSocket();
	void bindSocket();
	void listenClients();
};

