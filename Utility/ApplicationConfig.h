#pragma once


#ifdef JSONMANAGER_H
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif

#include<iostream>

class DECLSPEC ApplicationConfig
{
private:
	ApplicationConfig() {}
	/*
		Static instance of the class
	*/
	static ApplicationConfig* instance;
	std::string applicationWorkingDirectory;
	std::string connectionString;
	std::map<std::string, std::string> *config = nullptr;
	void readJsonFile(std::string);

public:
	// -------------  Singleton ApplicationCofig: Stopping copy constructor ----------- //
	ApplicationConfig(const ApplicationConfig&) = delete;
	~ApplicationConfig();

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
	std::string getConnectionString();
	void setConnectionString(std::string filePath);
	std::string getApplicationWorkingDirectory();
	void setApplicationWorkingDirectory(std::string);
	std::string get(std::string);
	void loadConfiguration(std::string);
};

