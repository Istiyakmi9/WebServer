#include "ApplicationConfig.h"
#include<mutex>
#include"Util.h"
#include<sstream>
#include"JsonManager.h"

std::mutex mtx;

ApplicationConfig* ApplicationConfig::instance = nullptr;

ApplicationConfig* ApplicationConfig::getInstance() {
	if (instance == nullptr) {
		std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
		mtx.lock(); {
			try {
				instance = new ApplicationConfig();
			}
			catch (int err) {
				mtx.unlock();
				return nullptr;
			}
		}
		mtx.unlock();
	}
	return ApplicationConfig::instance;
}

ApplicationConfig::~ApplicationConfig() {
	delete config;
}

std::string ApplicationConfig::getApplicationWorkingDirectory() {
	return this->applicationWorkingDirectory;
}

void ApplicationConfig::setApplicationWorkingDirectory(std::string pwd) {
	this->applicationWorkingDirectory = pwd;
}

std::string ApplicationConfig::getConnectionString() {
	return this->connectionString;
}

void ApplicationConfig::setConnectionString(std::string filePath) {
	this->connectionString = filePath;
}

std::string ApplicationConfig::get(std::string key) {
	std::string value = "";
	if (config != nullptr) {
		if (config->count(key) > 0) {
			value = config->find(key)->second;
		}
	}
	return value;
}

void ApplicationConfig::loadConfiguration(std::string filename) {
	readJsonFile(filename);
}

void ApplicationConfig::readJsonFile(std::string filename) {
	FILE* file;

	fopen_s(&file, Util::combine(this->getApplicationWorkingDirectory(), filename).c_str(), "r");
	if (file == NULL) {
		std::cerr << "Fail to read json file" << std::endl;
	}
	else {
		int i = 0;
		std::stringstream filedata;
		char ch = '\r';
		while (ch != EOF) {
			ch = fgetc(file);
			filedata << ch;
			i++;
		}

		std::unique_ptr<JsonManager> json(new JsonManager());
		config = json->toRequestMap(filedata.str());
	}

	delete file;
}