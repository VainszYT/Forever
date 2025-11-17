#include <python.h>

static std::string lastRead;

bool RunPythonFile(const char* filename) {
	std::string command = "python ";
	command += filename;
	
	int result = system(command.c_str());
	
	return(result == 0);
}

const char* ReadPythonFile(const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		lastRead = "ERROR: Couldnt open file";
		return lastRead.c_str();
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	lastRead = buffer.str();
	
	return lastRead.c_str();
}

bool WritePythonFile(const char* filename, const char* text) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	file << text;
	file.close();
	return true;
}