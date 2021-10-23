#include "DbUtility.h"
#include"DbContext.h"
#include<sstream>
#include"ApplicationConfig.h"
#include"Constants.h"
#include<exception>

std::string DbUtility::getResult(std::string procName, std::list<std::string> args, std::string outputKeyName) {
	std::string query = applicationConfig->get(procName);
	if (query != "") {
		if (args.size() > 0) {
			int index = 0;
			for (auto item : args) {
				index = 0;
				index = query.find("?", 0);
				if (index != -1) {
					query.replace(index, 1, item);
				}
			}
		}

		try {
			context = new DbContext(path.c_str());
			result = context->getResultSet(query.c_str());

			std::stringstream param;
			if (result->count("table") > 0) {
				if (outputKeyName != "")
					param << "\"" + outputKeyName + "\": " + result->find("table")->second;
				else
					param << result->find("table")->second;
			}
			else
				param << "";
			delete result;
			return param.str();
		}
		catch (const std::exception& ex) {
			delete result;
			std::cerr << ex.what() << std::endl;
		}
	}
	else {
		return procName + " not found.";
	}
}

bool DbUtility::IsDbExists() {
	bool fileExists = false;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	if (file) {
		fclose(file);
		fileExists = true;
	}
	return fileExists;
}

std::string DbUtility::execute(std::string procName, std::list<std::string> args) {
	if (IsDbExists()) {
		std::string query = applicationConfig->get(procName);
		if (query != "") {
			std::stringstream param;

			param << "(";
			int i = 0;
			while (i < args.size()) {
				if (i > 0)
					param << ",";
				param << args.front();
				i++;
			}

			param << ");";
			query.append(param.str());

			int count = context->executeNonQuery(query.c_str());
			if (count != 0)
				return "Fail";
			return "Success";
		}
		else {
			return "File: " + path + " not exists";
		}
	}
	else {
		return procName + " query not found";
	}
}