#pragma once

#include <exception>
#include <string>

class MissingComponentException : public std::exception 
{
public:

	MissingComponentException(std::string type)
	{
		message = "Missing Component! : '" + type + "' required!";
	}

	const char* what()
	{
		return message.c_str();
	}

private:
	std::string message;
};