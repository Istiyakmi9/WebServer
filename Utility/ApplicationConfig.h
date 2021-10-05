#pragma once

#include<iostream>

#ifdef JSONMANAGER_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

class DECLSPEC ApplicationConfig
{
private:
	ApplicationConfig() {}
	/*
		Static instance of the class
	*/
	static ApplicationConfig* instance;
	std::string applicationWorkingDirectory;

public:
	// -------------  Singleton ApplicationCofig: Stopping copy constructor ----------- //
	ApplicationConfig(const ApplicationConfig&) = delete;

	// -------------  Singleton ApplicationCofig object should not be assignabled ----------- //
	void operator=(const ApplicationConfig&) = delete;

	/*
		Static method to get only one instance of
		the object with thread safe approach
	*/
	static ApplicationConfig* getInstance();

	/*
		public method of singleton class
	*/
	std::string getApplicationWorkingDirectory();
	void setApplicationWorkingDirectory(std::string);
};

