#pragma once

#ifndef LOGGER_H_
#define LOGGER_H_

#include "Logger.h"
#include "windows.h"

void Logger::log(LogType type, std::string title, std::string content)
{
	std::string typeText;
	
	switch (type)
	{
	case INFO:
		printf(" [ \033[32mOKAY\033[0m ]");
		break;
	case WARNING:
		printf(" [ \033[33mSHIT\033[0m ]");
		break;
	case ERR:
		printf(" [ \033[31mFUCK\033[0m ]");
		break;
	case DEBUG:
		printf(" [ \033[36mDBUG\033[0m ]");
		break;
	default:
		break;
	}

	if (title.length() > 9)
	{
		printf(" <\033[95m%s\033[0m%-*c", title.substr(0, 8).c_str(), 4, '>');
	}
	else
	{
		printf(" <\033[95m%s\033[0m%-*c", title.c_str(), (12 - title.length()), '>');
	}

	std::cout << content << std::endl;
}

void Logger::logException(std::exception e)
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 12);
	std::cerr << "[EXEP]	<Exception>	  " << e.what() << std::endl;
	SetConsoleTextAttribute(console_color, 15);
}

#endif