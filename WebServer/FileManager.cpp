#include "FileManager.h"
#include<Windows.h>

FileManager::FileManager() {
	dbUtility = new DbUtility();
	fileDetail = new FileDetail();
}

FileManager::~FileManager() {
	delete dbUtility;
	delete fileDetail;
}

std::string FileManager::saveFile(std::string searchName, std::string path, std::string fileName, HttpRequest* httpRequest, long ownerUid) {
	std::unique_ptr<FileDetail> fileDetail = saveHttpRequestedFile("image", "UploadedFiles", "file.jpg", httpRequest);
	fileDetail->setFileOwnerId(ownerUid);
	std::string data = "";
	return data;
}

std::string FileManager::deleteFile(std::string path) {
	return "";
}

std::unique_ptr<FileDetail> FileManager::saveHttpRequestedFile(std::string searchName, std::string path, std::string fileName, HttpRequest* httpRequest) {
	std::string location = "";
	std::unique_ptr<FileDetail> fileDetail(new FileDetail());
	std::map<std::string, FormDataContainer*>* formDataContainerMap = httpRequest->getFromDataContainer();
	char* rawRequestData = httpRequest->getHttpRequestRawData();
	if (formDataContainerMap->count(searchName) > 0) {
		FormDataContainer* filePtr = formDataContainerMap->find(searchName)->second;
		fileDetail->setFileName(filePtr->getFilename());
		auto value = Util::splitter(fileName, ".");
		if (value->size() == 2) {
			fileDetail->setExtension(*(std::next(value->begin(), 1)));
		}
		value.release();

		ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
		location = Util::combine(applicationConfig->getApplicationWorkingDirectory(), path);

		if (CreateDirectory(location.c_str(), NULL)) {
			//------------- Directory created -----------------
			std::cout << "Folder create successfully" << std::endl;
		}
		else {
			//------------- Directory already exists -----------------
			std::cout << "Folder already exists" << std::endl;
		}

		fileDetail->setFilePath(Util::combine(path, fileName));
		std::string filePath = Util::combine(location, fileName);
		WIN32_FIND_DATA findFileData;
		HANDLE handle = FindFirstFile(filePath.c_str(), &findFileData);
		int found = handle != INVALID_HANDLE_VALUE;
		HANDLE fileHandler = NULL;
		if (found) {
			DeleteFile(filePath.c_str());
		}

		fileHandler = CreateFile(
			filePath.c_str(),
			GENERIC_WRITE,
			0,
			0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0
		);

		if (fileHandler) {
			std::cout << "File create successfully" << std::endl;
			long index = filePtr->getStartIndex();
			long endIndex = filePtr->getEndIndex();
			DWORD dwBytes = 0;
			while (index < endIndex) {
				WriteFile(
					fileHandler,
					&rawRequestData[index],
					1,
					&dwBytes,
					NULL
				);

				index++;
			}
			CloseHandle(fileHandler);
		}
		else {
			std::cout << "Fail to create file" << std::endl;
			return fileDetail;
		}
	}
	else {
		std::cerr << "No entry found with the name [" + fileName + "] in request form-data body." << std::endl;
	}
#ifdef  _WIN32

#elif __linux__

#endif //  _WIN32
	return fileDetail;
}