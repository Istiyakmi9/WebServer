#include<iostream>
#include<winsock2.h>
#include<Ws2tcpip.h>
#include<vector>
#include<chrono>
#include"ManageSocket.h"
#include"JsonManager.h"
#include<stdio.h>
#include"ApplicationConfig.h"
#include<list>
#include<direct.h>

#pragma comment (lib, "ws2_32.lib")

std::string current_working_directory()
{
	char* cwd = _getcwd(0, 0); // **** microsoft specific ****
	std::string working_directory(cwd);
	std::free(cwd);

	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	applicationConfig->setApplicationWorkingDirectory(working_directory);

	return working_directory;
}

void runAngular() {
	system("node E:/ui/shopmanager/server.js");
}

int main(int argc, char* argv[]) {
	//runAngular();
	current_working_directory();
	std::string databaseName = "Shop.db";
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getApplicationWorkingDirectory() + "\\" + databaseName;
	applicationConfig->setConnectionString(path);

	ManageSocket socket;
	socket.createSocket();

	return 0;
}