#include"DbContext.h"
#include"sqlite3.h"

int DbContext::executeNonQuery(const char* query) {
	sqlite3* db;
	int exit = 0;

	try {
		exit = sqlite3_open(path, &db);

		char* errorMessage = nullptr;
		exit = sqlite3_exec(db, query, NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			sqlite3_free(db);
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	sqlite3_close(db);
	return exit;
}

void DbContext::setResult(std::string value) {
	records << value;
}

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	DbContext* dbContext = static_cast<DbContext*>(NotUsed);
	int i = 0;
	std::string column = "";
	std::string value = "";
	std::string result;
	result.append(dbContext->seperater + "{");
	while (i < argc) {
		column = azColName[i];
		value = argv[i] ? argv[i] : "null";
		if (i != 0)
			result.append(",");
		result.append("\"" + column + "\": ");
		result.append("\"" + value + "\"");
		i++;
	}
	result.append("}");
	dbContext->seperater = ",";
	dbContext->setResult(result);
	return 0;
}

std::map<std::string, std::string>* DbContext::getResultSet(const char* query) {
	sqlite3* db;
	int exit = 0;
	records.str("");
	records.clear();
	seperater = "";
	resultSet = new std::map<std::string, std::string>();

	try {
		exit = sqlite3_open(path, &db);

		char* errorMessage = nullptr;
		exit = sqlite3_exec(db, query, callback, (void*)this, &errorMessage);

		if (exit != SQLITE_OK) {
			sqlite3_free(db);
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	sqlite3_close(db);
	resultSet->insert({ "table", "[" + records.str() + "]"});
	return std::move(this->resultSet);
}