#include"ManageSocket.h"
#include<Ws2tcpip.h>
#include<thread>
#include<vector>
#include"HttpContext.h"
#include<fstream>
#include <iterator>
#include <algorithm>

ManageSocket::ManageSocket() { }

///
/// Recieves data in to buffer until bufferSize value is met
///
int ManageSocket::RecvBuffer(SOCKET s, char* buffer, int bufferSize) {
	int i = 0;
	while (i < bufferSize) {
		const int l = recv(s, &buffer[i], __min(SendChunkSize, bufferSize - i), 0);
		if (l < 0) { return l; } // this is an error
		i += l;
	}
	return i;
}

/*
// Receives a file
// returns size of file if success
// returns -1 if file couldn't be opened for output
// returns -2 if couldn't receive file length properly
// returns -3 if couldn't receive file properly
*/
int ManageSocket::RecvFile(SOCKET s, const std::string& fileName) {
	std::ofstream file(fileName, std::ofstream::binary);
	if (file.fail()) { return -1; }

	int fileSize;
	if (RecvBuffer(s, reinterpret_cast<char*>(&fileSize),
		sizeof(fileSize)) != sizeof(fileSize)) {
		return -2;
	}

	char* buffer = new char[ReceivedChunkSize];
	bool errored = false;
	int i = fileSize;
	while (i != 0) {
		const int r = RecvBuffer(s, buffer, (int)__min(i, (int)ReceivedChunkSize));
		if ((r < 0) || !file.write(buffer, r)) { errored = true; break; }
		i -= r;
	}
	delete[] buffer;

	file.close();

	return errored ? -3 : fileSize;
}

void ManageSocket::GetSenderDetail(sockaddr_in client) {
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
	//unsigned int __stdcall handleRequest(void *args) {
	SOCKET* descriptor = (SOCKET*)lpParameter;
	SOCKET clientSocketDescriptor = *descriptor;
	if (clientSocketDescriptor != -1) {
		// While loop: accept and echo message back to client
		const int BUFFERSIZE = 20 * 1024;
		std::vector<char>* buffer = new std::vector<char>(BUFFERSIZE);

		memset(buffer->data(), 0, BUFFERSIZE);
		//wait for client to send data
		int bytesReceived = recv(clientSocketDescriptor, reinterpret_cast<char*>(buffer->data()), BUFFERSIZE, 0);
		if (bytesReceived == SOCKET_ERROR) {
			std::cout << "Connection closed." << std::endl;
		}
		else {

			if (bytesReceived == 0) {
				std::cout << "Client diconnected " << std::endl;
			}
			else {
				// echo message back to client
				int len = bytesReceived - 1;
				std::unique_ptr<HttpContext> context(std::make_unique<HttpContext>(buffer, bytesReceived));
				std::string response = "";
				if (context->getRequestType() != "OPTIONS")
					response = context->handleIncomingRequest();
				else {
					//buffer->resize(bytesReceived);
					//response = buffer->data();
					//response.append("Access-Control-Allow-Origin: *");

					response.append("HTTP/1.1 204 No Content\r\n"
						"Connection: keep-alive\r\n"
						"Content-Type: application/json; charset=UTF-8\r\n"
						"Access-Control-Allow-Origin: *\r\n"
						"Access-Control-Allow-Methods: POST, GET, OPTIONS, DELETE\r\n"
						"Access-Control-Max-Age: 86400\r\n"
						"Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With\r\n"
					);
				}
				send(clientSocketDescriptor, response.c_str(), strlen(response.c_str()), 0);
			}
		}

		delete buffer;
		// Close the socket 
		closesocket(clientSocketDescriptor);
	}
	return 0;
}

int ManageSocket::createSocket() {
	// Initilize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);
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
		//std::thread t(handleRequest, clientSocket);

		//HANDLE clientThreadHandler = NULL;
		CreateThread(0, 0, handleRequest, (void*)&clientSocket, 0, 0);
	}

	// Close listening socket
	closesocket(listening);

	// Cleanup winsock
	WSACleanup();
	std::cout << "Socket closed successfully";
	return 0;
}

void ManageSocket::bindSocket() {

}

void ManageSocket::listenClients() {

}