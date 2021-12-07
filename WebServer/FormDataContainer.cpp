#include"FormDataContainer.h"

FormDataContainer::FormDataContainer() {
	setFileContentType("");
}

std::string FormDataContainer::getContentDisposition() { 
	return contentDisposition;
}

void FormDataContainer::setContentDisposition(std::string value) { 
	contentDisposition = value;
}

std::string FormDataContainer::getFileContentType() { 
	return fileContentType;
}

void FormDataContainer::setFileContentType(std::string value) { 
	fileContentType = value;
}

std::string FormDataContainer::getFilename() { 
	return filename;
}

void FormDataContainer::setFilename(std::string value) { 
	filename = value;
}

std::string FormDataContainer::getName() { 
	return name;
}

void FormDataContainer::setName(std::string value) { 
	name = value;
}

long FormDataContainer::getStartIndex() {
	return startIndex;
}

void FormDataContainer::setStartIndex(long value) {
	startIndex = value;
}


long FormDataContainer::getEndIndex() {
	return endIndex;
}

void FormDataContainer::setEndIndex(long value) {
	endIndex = value;
}