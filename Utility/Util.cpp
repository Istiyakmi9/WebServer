#include"Util.h"
#include<sstream>
#include<chrono>
#include<ctime>

std::string Util::toUpper(std::string arg) {
	std::stringstream data;
	if (arg != "") {
		int index = 0;
		while (index < arg.length()) {
			data << (char)std::toupper(arg[index]);
			index++;
		}
	}
	return data.str();
}

std::string Util::toLower(std::string arg) {
	std::stringstream data;
	if (arg != "") {
		int index = 0;
		while (index < arg.length()) {
			data << (char)std::tolower(arg[index]);
			index++;
		}
	}
	return data.str();
}

std::string Util::toCapitalize(std::string arg) {
	std::stringstream data;
	if (arg != "") {
		int index = 0;
		while (index < arg.length()) {
			if (index == 0)
				data << (char)std::tolower(arg[index]);
			else {
				if (arg[index] == ' ') {
					index++;
					continue;
				}
				data << arg[index];
			}
			index++;
		}
	}
	return data.str();
}

std::string Util::combine(std::string arg0, std::string arg1) {
	return arg0 + "\\" + arg1;
}

std::string Util::SqlStringValue(std::string value) {
	return "'" + value + "'";
}

std::string Util::SqlValue(int value) {
	return std::to_string(value);
}

std::string Util::SqlValue(long value) {
	return std::to_string(value);
}

std::string Util::SqlCurrentDateTime() {
	std::time_t now = std::time(0);
	struct tm timestruct;
	char buf[80];
	localtime_s(&timestruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &timestruct);
	return buf;
}

void Util::ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void Util::rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

void Util::trim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));

	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

std::map<std::string, std::string>* Util::jsonToMap(std::string sourceString) {
	std::map<std::string, std::string>* result = new std::map<std::string, std::string>();
	auto items = Util::splitter(sourceString, ";");

	std::string token;
	size_t pos = 0;
	std::string delimiter = ": ";
	auto ptr = items->begin();
	while (ptr != items->end()) {
		if ((pos = sourceString.find(delimiter)) != std::string::npos) {
			token = ptr->substr(0, pos);
			Util::trim(token);
			ptr->erase(0, pos + delimiter.length());
			Util::trim(*ptr);
		}

		result->insert({ token, sourceString });
		ptr++;
	}

	items.release();
	return result;
}

std::unique_ptr<std::list<std::string>> Util::singleSplitter(std::string sourceString, std::string delimiter) {
	std::unique_ptr<std::list<std::string>> result(std::make_unique<std::list<std::string>>());
	size_t pos = 0;
	std::string token;
	if ((pos = sourceString.find(delimiter)) != std::string::npos) {
		token = sourceString.substr(0, pos);
		Util::trim(token);
		result->push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}

	Util::trim(sourceString);
	result->push_back(sourceString);
	return result;
}

std::unique_ptr<std::list<std::string>> Util::splitter(std::string sourceString, std::string delimiter) {
	std::unique_ptr<std::list<std::string>> result(std::make_unique<std::list<std::string>>());
	size_t pos = 0;
	std::string token;
	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		token = sourceString.substr(0, pos);
		Util::trim(token);
		result->push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}

	Util::trim(sourceString);
	result->push_back(sourceString);
	return result;
}

std::string Util::replace_all(std::string s, std::string find, std::string replace) {
	int i = 0;
	int pos = 0;
	std::stringstream ss;
	while (i < s.length()) {
		pos = s.find(find, i);
		if (pos != -1) {
			ss << s.substr(i, (pos - i));
			ss << replace;
			i = pos + replace.length() + 1;
			continue;
		}
		else {
			return s;
		}
	}
	return ss.str();
}