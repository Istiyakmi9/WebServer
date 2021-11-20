#include"Util.h"
#include<sstream>
#include<chrono>
#include<ctime>

std::string Util::toUpper(std::string arg) {
	std::stringstream data;
	if (arg != "") {
		int index = 0;
		while (index < arg.length()) {
			data << std::toupper(arg[index]);
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
			data << std::tolower(arg[index]);
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
				data << std::tolower(arg[index]);
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
	return value;
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