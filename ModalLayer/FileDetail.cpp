#include"FileDetail.h"

std::string FileDetail::getExtension() { 
	return Extension;
}

void FileDetail::setExtension(std::string value) { 
	Extension = value;
}

long FileDetail::getFileDetailId() { 
	return FileDetailId;
}

void FileDetail::setFileDetailId(long value) { 
	FileDetailId = value;
}

std::string FileDetail::getFileName() { 
	return FileName;
}

void FileDetail::setFileName(std::string value) { 
	FileName = value;
}

long FileDetail::getFileOwnerId() { 
	return FileOwnerId;
}

void FileDetail::setFileOwnerId(long value) { 
	FileOwnerId = value;
}

std::string FileDetail::getFilePath() { 
	return FilePath;
}

void FileDetail::setFilePath(std::string value) { 
	FilePath = value;
}


void FileDetail::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FileDetailFuncNames>> FuncIds(new std::map<std::string, FileDetailFuncNames>());
	FuncIds->insert({ "setExtension", FileDetailFuncNames::setExtension });
	FuncIds->insert({ "setFileDetailId", FileDetailFuncNames::setFileDetailId });
	FuncIds->insert({ "setFileName", FileDetailFuncNames::setFileName });
	FuncIds->insert({ "setFileOwnerId", FileDetailFuncNames::setFileOwnerId });
	FuncIds->insert({ "setFilePath", FileDetailFuncNames::setFilePath });


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	FileDetailFuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		fnName[0] = std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {
			case FileDetailFuncNames::setExtension:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setExtension(value); 
				}
				break; 
			case FileDetailFuncNames::setFileDetailId:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setFileDetailId(value); 
				}
				break; 
			case FileDetailFuncNames::setFileName:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFileName(value); 
				}
				break; 
			case FileDetailFuncNames::setFileOwnerId:
				{
					long value = JsonManager::ConvertTo<long>(item->second);
					setFileOwnerId(value); 
				}
				break; 
			case FileDetailFuncNames::setFilePath:
				{
					std::string value = JsonManager::ConvertTo<std::string>(item->second);
					setFilePath(value); 
				}
				break; 
			}
		}
	}
	delete requestMap;
}
