#include "utils.hpp"
#include <ctime>
#include <sstream>

std::string intToString(int toStr)
{
	std::stringstream ss;
	ss << toStr;
	return ss.str();
}

std::string getDateCreation(void)
{
	std::time_t			now = std::time(NULL);
	struct std::tm *timeinfo = std::localtime(&now);

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	std::string result = buffer;
	return result;
}

