#include"HttpResponse.h"
#include"HttpContext.h"
#include<string>

HttpResponse::HttpResponse() { }

std::string HttpResponse::getHttpResponseString(int flag, std::string responseData, std::map<std::string, std::string> *customHeaders) {
	char buffer[32];
	time_t now = time(0);
	ctime_s(buffer, 32, &now);
	std::string responseString; 
	responseString.append("HTTP/1.1 " + std::to_string(flag) + " OK\n");
	responseString.append("Date: " + std::string(buffer) + " GMT\n");
	responseString.append("Server: Bottomhalf C++ Server\n");
	responseString.append("Last-Modified: " + std::string(buffer) + " GMT\n");
	responseString.append("Authorization: temp_token_asdklfuoas789faysofjasdflsdjf\n");	

	if (customHeaders != nullptr) {
		for (auto item : *customHeaders) {
			responseString.append(item.first + ": " + item.second + "\n");
		}
	}

	responseString.append("Content-Length: "+ std::to_string(responseData.length()) +"\n");
	responseString.append("Accept-Ranges: bytes\n");
	responseString.append("Connection: close\n");
	responseString.append("\n");
	responseString.append(responseData);
	return responseString;
}