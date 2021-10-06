#include"JsonManager.h"
#include<list>
#include <functional>
#include<iostream>
#include<string>
#include<sstream>

// trim from start (in place)
void JsonManager::ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
void JsonManager::rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
void JsonManager::trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

std::string JsonManager::stringify(std::string key, std::string value) {
	std::string jsonObject;
	jsonObject.append("{");
	jsonObject.append("\"" + key + "\": ");
	jsonObject.append("\"" + value + "\"");
	jsonObject.append("}");
	return jsonObject;
}

std::unique_ptr<std::list<std::string>> JsonManager::splitter(std::string sourceString, std::string delimiter) {
	std::unique_ptr<std::list<std::string>> result(std::make_unique<std::list<std::string>>());
	size_t pos = 0;
	std::string token;
	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		token = sourceString.substr(0, pos);
		trim(token);
		if (token != "")
			result->push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}
	trim(sourceString);
	if (sourceString != "")
		result->push_back(sourceString);
	return result;
}

std::unique_ptr<std::list<std::string>> JsonManager::firstSplitter(std::string sourceString, std::string delimiter) {
	std::unique_ptr<std::list<std::string>> result(std::make_unique<std::list<std::string>>());
	size_t pos = 0;
	std::string token;
	if ((pos = sourceString.find(delimiter)) != std::string::npos) {
		token = sourceString.substr(0, pos);
		trim(token);
		if (token != "")
			result->push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}
	trim(sourceString);
	if (sourceString != "")
		result->push_back(sourceString);
	return result;
}

std::map<std::string, std::string>* JsonManager::toRequestMap(std::string json) {
	std::map<std::string, std::string>* jsonObject = new std::map<std::string, std::string>();
	if (json != "") {
		bool isObjectFound = false;
		bool isKey = true;
		bool isEscape = false;
		std::ostringstream lineStream;
		std::string key = "";
		std::string value = "";

		int index = 0;
		while (index < json.length()) {
			switch (json[index]) {
			case '{':
				isObjectFound = true;
				break;
			case '\r':
				break;
			case '\n':
				break;
			case '}':
			case ',': {
				isObjectFound = false;
				value = lineStream.str();
				trim(value);
				jsonObject->insert({ key, value });
				key = "";
				value = "";
				lineStream.str("");
				lineStream.clear();
			}
					break;
			case ':':
			{
				isKey = false;
				key = lineStream.str();
				trim(key);
				lineStream.str("");
				lineStream.clear();
			}
			break;
			default:
			{
				if (json[index] == '\"') {
					index++;
					while (json[index] != '\"' && index < json.length()) {
						if (json[index] != '\r' && json[index] != '\n') {
							lineStream << json[index];
						}
						index++;
					}
				}
			}
			break;
			}
			index++;
		}
	}

	return jsonObject;
}