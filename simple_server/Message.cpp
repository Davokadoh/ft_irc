#include "../inc/Message.hpp"

Message::Message(void) : _nick(""), _hostName(""), _cmd("") {}

Message::~Message(void) {}

void	Message::splitData(std::string tmp)
{
	std::istringstream	iss(tmp);
	std::string token;

	while (iss >> token)
		this->_param.push_back(token);
}

void	Message::srcSplit(void)
{
	std::istringstream	buffer(this->_src);

	std::getline(buffer, this->_nick, '!');
	this->_nick.erase(0, 1);
	std::getline(buffer, this->_user, '@');
	std::getline(buffer, this->_hostName, '\0');
}

void	Message::parse(std::string toParse)
{
	std::istringstream	buffer(toParse);
	std::string			tmp;
	if (toParse[0] == ':')
		std::getline(buffer, this->_src, ' ');
	std::getline(buffer, this->_cmd, ' ');
	std::getline(buffer, tmp, ':');
	this->splitData(tmp);
	tmp.erase();
	std::getline(buffer, tmp, '\n');
	if (!tmp.empty())
		this->_param.push_back(tmp);
	this->srcSplit();
	this->printTest();
}

void	Message::clearParam(void)
{
	this->_nick = "";
	this->_hostName = "";
	this->_cmd = "";
	this->_param.clear();
}

void	Message::printTest(void)
{
	std::cout << "Src: " << this->_src << std::endl;
	std::cout << "Nick: " << this->_nick << std::endl;
	std::cout << "User: " << this->_user << std::endl;
	std::cout << "Hostname: " << this->_hostName << std::endl;
	std::cout << "Cmd: " << this->_cmd << std::endl;
	std::cout << "Params: ";
	std::vector<std::string>::iterator	it = this->_param.begin();
	for (; it != this->_param.end(); it++)
	{
		std::cout << *it << " | ";
	}
	std::cout << std::endl;
}
