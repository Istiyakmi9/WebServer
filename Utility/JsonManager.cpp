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

std::string JsonManager::stringify(std::map<std::string, std::string>* p) {
	std::stringstream data;
	data << "{";

	int i = 0;
	for (auto item = p->begin(); item != p->end(); item++) {
		if (i != 0)
			data << ", ";
		data << "\"" + item->first + "\": " + item->second + "";
		i++;
	}

	data << "}";
	return data.str();
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
				else {
					while (json[index] != ',' && index < json.length()) {
						if (json[index] != '\r' && json[index] != '\n') {
							lineStream << json[index];
						}

						if (json[index] != ',')
							break;
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

struct tm* JsonManager::ConvertToDateTime(const std::string& value) {
	// Let's consider we are getting all the input in
	// this format: '2014-07-25T20:17:22Z' (T denotes
	// start of Time part, Z denotes UTC zone).
	// A better approach would be to pass in the format as well.
	std::wstring dateTime(value.length(), L' ');
	std::copy(value.begin(), value.end(), dateTime.begin());
	static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };

	// Create a stream which we will use to parse the string,
	// which we provide to constructor of stream to fill the buffer.
	std::wistringstream ss{ dateTime };

	// Create a tm object to store the parsed date and time.
	std::tm dt;

	// Now we read from buffer using get_time manipulator
	// and formatting the input appropriately.
	ss >> std::get_time(&dt, dateTimeFormat.c_str());

	// Convert the tm structure to time_t value and return.
	time_t rawtime = std::mktime(&dt);

	struct tm* tminfo = new tm();

	time(&rawtime);
	localtime_s(tminfo, &rawtime);
	return tminfo;
}