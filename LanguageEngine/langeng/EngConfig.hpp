#pragma once

/*! \mainpage Language Engine
	Language Engine is translation library
*/

#include <cstdint>
#include <string>

//Use std::exception for exception handeling
#define LANGENG_USE_EXCEPTION

//Use default behaviour for error id type
#define LANGENG_USE_DEFAULT_ACTION

struct LANGENG_VERSION
{
	static const uint32_t major = 1;
	static const uint32_t minor = 1;
	static const uint32_t bugFixed = 0;

	static std::string toString()
	{
		return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(bugFixed);
	}
};