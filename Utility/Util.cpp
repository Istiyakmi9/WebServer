#include"Util.h"
#include<sstream>

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