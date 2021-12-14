#include "FileManager.h"
#include<Windows.h>

FileManager::FileManager() {
	dbUtility = new DbUtility();
}

FileManager::~FileManager() {
	delete dbUtility;
}

bool FileManager::insertRecord(FileDetail* fileDetail) {
	std::string procedureName = "InsertFileDetail";
	std::list<std::string> params;
	params.push_back(Util::SqlStringValue(fileDetail->getFileName()));
	params.push_back(Util::SqlStringValue(fileDetail->getFilePath()));
	params.push_back(Util::SqlStringValue(fileDetail->getExtension()));
	params.push_back(Util::SqlValue(fileDetail->getFileOwnerId()));
	params.push_back("Date()");
	params.push_back(Util::SqlStringValue(""));

	std::string data = dbUtility->execute(procedureName, params);
	bool flag = true;
	if (data == "")
		flag = false;
	return flag;
}

bool FileManager::updateRecord(FileDetail* fileDetail) {
	std::string procedureName = "UpdateFileDetail";
	std::list<std::string> params;
	params.push_back(Util::SqlStringValue(fileDetail->getFileName()));
	params.push_back(Util::SqlStringValue(fileDetail->getFilePath()));
	params.push_back(Util::SqlStringValue(fileDetail->getExtension()));
	params.push_back(Util::SqlValue(fileDetail->getFileOwnerId()));
	params.push_back("Date()");
	params.push_back(Util::SqlValue(fileDetail->getFileDetailId()));

	std::string data = dbUtility->execute(procedureName, params);
	bool flag = true;
	if (data == "")
		flag = false;
	return flag;
}

std::string FileManager::saveFile(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest) {
	std::string response = "";
#ifdef  _WIN32
	saveHttpRequestedFile(searchName, fileDetail, httpRequest);
#elif __linux__

#endif //  _WIN32
	std::string data = dbUtility->getResult("SelectFileDetail", { Util::SqlValue(fileDetail->getFileDetailId()) });
	if (data == "" || data == "[]") {
		this->insertRecord(fileDetail);
		response = "Created successfully";
	}
	else {
		auto record = JsonManager::toRequestMap(data);
		if (record->count("FilePath") > 0) {
			ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
			std::string path = Util::combine(applicationConfig->getApplicationWorkingDirectory(), record->find("FilePath")->second);
			this->deleteFile(path);
		}
		this->updateRecord(fileDetail);
		response = "Updated successfully";
	}
	return response;
}

std::string FileManager::deleteFile(std::string path) {
	WIN32_FIND_DATA findFileData;
	HANDLE handle = FindFirstFile(path.c_str(), &findFileData);
	int found = handle != INVALID_HANDLE_VALUE;
	HANDLE fileHandler = NULL;
	if (found) {
		DeleteFile(path.c_str());
	}
	return "File deleted successfully";
}

void FileManager::saveHttpRequestedFile(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest) {
	std::string location = "";
	std::string fileName = "";
	std::map<std::string, FormDataContainer*>* formDataContainerMap = httpRequest->getFromDataContainer();
	char* rawRequestData = httpRequest->getHttpRequestRawData();
	if (formDataContainerMap->count(searchName) > 0) {
		FormDataContainer* filePtr = formDataContainerMap->find(searchName)->second;
		fileName = filePtr->getFilename();
		fileDetail->setFileName(fileName);

		auto value = Util::splitter(fileName, ".");
		if (value->size() == 2) {
			fileDetail->setExtension(*(std::next(value->begin(), 1)));
		}
		value.release();

		ApplicationConfig* applicationConfig = ApplicationConfig::getInstance();
		location = Util::combine(applicationConfig->getApplicationWorkingDirectory(), fileDetail->getFilePath());

		if (CreateDirectory(location.c_str(), NULL)) {
			//------------- Directory created -----------------
			std::cout << "Folder create successfully" << std::endl;
		}
		else {
			//------------- Directory already exists -----------------
			std::cout << "Folder already exists" << std::endl;
		}

		std::string filePath = Util::combine(location, fileName);
		std::string dbFilePath = Util::combine(fileDetail->getFilePath(), fileName);
		dbFilePath = Util::replace_all(dbFilePath, "\\", "\\\\");
		fileDetail->setFilePath(dbFilePath);
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
		}
	}
	else {
		std::cerr << "No entry found with the name [" + fileName + "] in request form-data body." << std::endl;
	}
}

void FileManager::saveHttpRequestedFile_Unix(std::string searchName, FileDetail* fileDetail, HttpRequest* httpRequest) {

}