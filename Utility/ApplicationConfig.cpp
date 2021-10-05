#include "ApplicationConfig.h"
#include<mutex>

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


std::string ApplicationConfig::getApplicationWorkingDirectory() {
	return this->applicationWorkingDirectory;
}

void ApplicationConfig::setApplicationWorkingDirectory(std::string pwd) {
	this->applicationWorkingDirectory = pwd;
}