




void UserDetail::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	FuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {

			}
		}
	}
}





void ProductModal::setPrivateFieldsValue(std::string json) {
	std::unique_ptr<std::map<std::string, FuncNames>> FuncIds(new std::map<std::string, FuncNames>());


	std::map<std::string, std::string>* requestMap = JsonManager::toRequestMap(json);

	FuncNames name;
	std::string fnName = "";
	for (auto item = requestMap->begin(); item != requestMap->end(); item++) {
		fnName = item->first;
		std::toupper(fnName[0]);
		fnName = "set" + fnName;
		if (FuncIds->count(fnName) > 0) {
			name = FuncIds->find(fnName)->second;
			switch (name) {

			}
		}
	}
	delete requestMap;
}
