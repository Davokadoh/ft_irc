#include "../inc/Message.hpp"

Message::Message(void) : _src(""), _nick(""), _user(""), _hostname(""), _verb("") {}

Message::~Message(void) {}

// ------- GETTER AND SETTER -------

std::string	Message::getSrc(void) const
{
	return (this->_src);
}

std::string Message::getNick(void) const
{
	return (this->_nick);
}

std::string	Message::getUser(void) const
{
	return (this->_user);
}

std::string	Message::getHostname(void) const
{
	return (this->_hostname);
}

std::string	Message::getVerb(void) const
{
	return (this->_verb);
}

std::vector<std::string>	Message::getParameters(void) const
{
	return (this->_parameters);
}

void	Message::setSrc(std::string str)
{
	this->_src = str;
}

void	Message::setNick(std::string str)
{
	this->_nick = str;
}

void	Message::setUser(std::string str)
{
	this->_user = str;
}

void	Message::setHostname(std::string str)
{
	this->_hostname = str;
}

void	Message::setVerb(std::string str)
{
	this->_verb = str;
}

// ------- MEMBER FONCTIONS -------

void	Message::splitData(std::string tmp)
{
	std::istringstream	iss(tmp);
	std::string token;

	while (iss >> token)
		this->_parameters.push_back(token);
}

void	Message::srcSplit(void)
{
	std::istringstream	buffer(this->_src);

	std::getline(buffer, this->_nick, '!');
	std::getline(buffer, this->_user, '@');
	std::getline(buffer, this->_hostname, '\0');
}

void	Message::parse(std::string toParse)
{
	std::istringstream	buffer(toParse);
	std::string			tmp;

	if (toParse[0] == ':')
	{
		std::getline(buffer, this->_src, ' ');
		this->_src.erase(0, 1);
	}
	std::getline(buffer, this->_verb, ' ');
	std::getline(buffer, tmp, ':');
	if (!tmp.empty())
	{
		this->splitData(tmp);
		tmp.erase();
	}
	std::getline(buffer, tmp, '\n');
	if (tmp.back() == '\r')
		tmp.pop_back();
	if (!tmp.empty())
		this->_parameters.push_back(tmp);
	this->srcSplit();
	this->printTest();
}

void	Message::printTest(void)
{
	std::vector<std::string> tmp = this->getParameters();

	std::cout << "Src: " << this->getSrc()<< std::endl;
	std::cout << "Nick: " << this->getNick() << std::endl;
	std::cout << "User: " << this->getUser() << std::endl;
	std::cout << "hostname: " << this->getHostname() << std::endl;
	std::cout << "Verb: " << this->getVerb() << std::endl;
	std::cout << "Parameters: ";
	std::vector<std::string>::iterator	it = tmp.begin();
	for (; it != tmp.end(); it++)
	{
		std::cout << *it << " | ";
	}
	std::cout << std::endl;
}
