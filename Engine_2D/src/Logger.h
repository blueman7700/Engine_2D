#pragma once

#include <iostream>
#include <string>

enum LogType
{
	INFO,
	WARNING,
	ERR,
	DEBUG
};

class Logger
{

public:

	static void log(LogType type, std::string title, std::string content);
	static void logException(std::exception e);

private:


};

