#include"SocketLayer.h"
#include<Ws2tcpip.h>
#include<thread>
#include<vector>
#include"HttpContext.h"
#include<fstream>
#include <iterator>
#include <algorithm>

SocketLayer::SocketLayer() {
	frontController = FrontController::InstanceOf();
}

void SocketLayer::GetSenderDetail(sockaddr_in client) {
	char host[NI_MAXHOST];			//  client's remote name
	char service[NI_MAXSERV];		// Service (i.e port) the client is connect on

	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << " connect on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connect on port " <<
			ntohs(client.sin_port) << std::endl;
	}
}

DWORD WINAPI handleRequest(__in LPVOID lpParameter) {
	SOCKET* descriptor = (SOCKET*)lpParameter;
	SOCKET clientSocketDescriptor = *descriptor;
	std::string methodType = "";
	if (clientSocketDescriptor != -1) {
		// While loop: accept and echo message back to client
		//std::map<std::string, std::string>* headers = new std::map<std::string, std::string>();
		int BUFFERSIZE = 2 * 1024 * 1024;
		//std::vector<char>* buffer = new std::vector<char>(BUFFERSIZE);
		char* buffer = new char[BUFFERSIZE];

		//wait for client to send data

		bool firstLineFlag = true;
		int bytesReceived = 0;

		//bytesReceived = recv(clientSocketDescriptor, reinterpret_cast<char*>(buffer->data()), BUFFERSIZE, 0);
		bytesReceived = recv(clientSocketDescriptor, buffer, BUFFERSIZE, 0);

		int len = bytesReceived - 1;
		std::string responseMessage = "";
		HttpContext* context = new HttpContext(buffer, bytesReceived);
		if (context->getRequestType() == "OPTIONS") {
			responseMessage.append("HTTP/1.1 204 No Content\r\n"
				"Connection: keep-alive\r\n"
				"Content-Type: application/json; charset=UTF-8\r\n"
				"Access-Control-Allow-Origin: *\r\n"
				"Access-Control-Allow-Methods: POST, GET, OPTIONS, DELETE\r\n"
				"Access-Control-Max-Age: 86400\r\n"
				"Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With\r\n"
			);
			send(clientSocketDescriptor, responseMessage.c_str(), strlen(responseMessage.c_str()), 0);
		}
		else {
			switch (context->getHttpRequest()->requestedType) {
			case 1: {
				auto frontController = FrontController::InstanceOf();

				responseMessage = frontController->CallToController(context);
				if (responseMessage.find("{", 0) == std::string::npos) {
					if (responseMessage == "")
						responseMessage = "\"\"";
					else
						responseMessage = "\"" + responseMessage + "\"";
				}

				responseMessage = context->getHttpResponse(responseMessage);
				send(clientSocketDescriptor, responseMessage.c_str(), strlen(responseMessage.c_str()), 0);
			}
				  break;
			case 2: {
				ULONGLONG FileSize = 0;
				ApplicationConfig* config = ApplicationConfig::getInstance();
				std::string localFilePath = Util::combine(config->getApplicationWorkingDirectory(), context->getHttpRequest()->staticFilePath);
				responseMessage = context->getHttpResponseForStaticFile(localFilePath, FileSize);
				send(clientSocketDescriptor, responseMessage.c_str(), FileSize, 0);
			}
				  break;
			}
		}

		if (buffer != nullptr)
			delete[] buffer;
		closesocket(clientSocketDescriptor);
		delete context;
	}
	return 0;
}

int SocketLayer::createSocket() {
	// Initilize winsock
	WSADATA wsData;

	int wsok = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (wsok != 0) {
		std::cerr << "Can't Initialize winsock! Quiting" << std::endl;
		return -1;
	}

	// Create a socket 
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return -1;
	}

	// Bind the ip address and port to a socket
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(9100);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell winsock the socket is ready for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket;
	while (1) {
		std::cout << "[BottomHalf WebServer]: Started - Waiting for client to join" << std::endl;

		// GetSenderDetail(client);

		clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Can't accept client request! Qutting" << std::endl;
			break;
		}

#if defined _WIN32
		u_long iMode = 1;
		int len = ioctlsocket(clientSocket, FIONBIO, &iMode);
		if (len != NO_ERROR) {
			std::cerr << "Can't create a socket! Quitting id: " << len << std::endl;
			return -1;
		}
#endif

		/*----------  Login to read file ---------------*/
		//RecvFile(clientSocket, "test.txt");

		std::cout << "[BottomHalf WebServer]: Client request received." << std::endl;
		std::cout << "[BottomHalf WebServer]: Starting seperate thread to handle the incoming request." << std::endl;

		CreateThread(0, 0, handleRequest, (void*)&clientSocket, 0, 0);
	}

	// Close listening socket
	closesocket(listening);

	// Cleanup winsock
	WSACleanup();
	std::cout << "Socket closed successfully";
	return 0;
}

void SocketLayer::bindSocket() {

}

void SocketLayer::listenClients() {

}