#pragma once

#include<iostream>
#include<winsock2.h>

class ManageSocket
{
private:
	int ReceivedChunkSize = 512;
	int SendChunkSize = 4 * 1024;
	void GetSenderDetail(sockaddr_in client);
	int RecvFile(SOCKET s, const std::string& fileName);
	int RecvBuffer(SOCKET s, char* buffer, int bufferSize);

public:
	explicit ManageSocket();
	int createSocket();
	void bindSocket();
	void listenClients();
};

