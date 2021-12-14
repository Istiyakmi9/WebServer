#include<winsock2.h>
#include<Ws2tcpip.h>
#include<vector>
#include<chrono>
#include"SocketLayer.h"
#include"JsonManager.h"
#include<stdio.h>
#include"ApplicationConfig.h"
#include<list>
#include<direct.h>
#include<iostream>
#include"Util.h"
#include<sstream>

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

void testVa(int num, ...) {
	va_list args;

	va_start(args, num);

	for (int i = 0; i < num; i++) {
		auto value = va_arg(args, int);
		printf("%d:  %d\n", i, value);
	}

	va_end(args);
}

int main(int argc, char* argv[]) {
	//runAngular();

	/*-------------- getting application working directory -------------------*/
	current_working_directory();

	/*-------------- application used database name -------------------*/
	std::string databaseName = "Shop.db";


	/*-------------- Creating singleton object for ApplicationConfig class -------------------*/
	ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
	std::string path = applicationConfig->getApplicationWorkingDirectory() + "\\" + databaseName;
	
	/*-------------- Setting up database connection string -------------------*/
	applicationConfig->setConnectionString(path);

	/*-------------- configure and read application json file -------------------*/
	applicationConfig->loadConfiguration("procedures.json");

	SocketLayer socket;
	socket.createSocket();

	return 0;
}