#include "../inc/Message.hpp"

// ------- COPLIEN -------

Message::Message(void)
{
    this->_src = "";
    this->_nick = "";
    this->_user = "";
    this->_hostname = "";
    this->_verb = "";
}

Message::Message(const Message &rhs)
{
    *this = rhs;
}

Message &Message::operator=(const Message &rhs)
{
    if (this != &rhs)
    {
        this->_src = rhs._src;
        this->_nick = rhs._nick;
        this->_user = rhs._user;
        this->_hostname = rhs._hostname;
        this->_verb = rhs._verb;
        this->_parameters = rhs._parameters;
    }
    return (*this);
}

Message::~Message(void)
{
}

// ------- GETTER AND SETTER -------

std::string Message::getSrc(void) const
{
    return (this->_src);
}

std::string Message::getNick(void) const
{
    return (this->_nick);
}

std::string Message::getUser(void) const
{
    return (this->_user);
}

std::string Message::getHostname(void) const
{
    return (this->_hostname);
}

std::string Message::getVerb(void) const
{
    return (this->_verb);
}

std::vector<std::string> Message::getParameters(void) const
{
    return (this->_parameters);
}

void Message::setSrc(std::string str)
{
    this->_src = str;
}

void Message::setNick(std::string str)
{
    this->_nick = str;
}

void Message::setUser(std::string str)
{
    this->_user = str;
}

void Message::setHostname(std::string str)
{
    this->_hostname = str;
}

void Message::setVerb(std::string str)
{
    this->_verb = str;
}

// ------- MEMBER FONCTIONS -------

void Message::splitParameters(std::string tmp)
{
    std::istringstream iss(tmp);
    std::string        token;

    while (iss >> token)
    {
        this->_parameters.push_back(token);
    }
}

void Message::srcSplit(void)
{
    std::istringstream buffer(this->_src);

    std::getline(buffer, this->_nick, '!');
    std::getline(buffer, this->_user, '@');
    std::getline(buffer, this->_hostname);
}

void Message::parse(std::string toParse)
{
    std::istringstream buffer(toParse);
    std::string        tmp;

    if (toParse[0] == ':')
    {
        std::getline(buffer, this->_src, ' ');
        this->_src.erase(0, 1);
        this->srcSplit();
    }
    std::getline(buffer, this->_verb, ' ');
    std::getline(buffer, tmp, ':');
    if (!tmp.empty())
    {
        this->splitParameters(tmp);
        tmp.erase();
    }
    std::getline(buffer, tmp, '\n');

    if (!tmp.empty())
    {
        this->_parameters.push_back(tmp);
    }
    // this->print();
}

void Message::clear(void)
{
    this->_src.clear();
    this->_nick.clear();
    this->_user.clear();
    this->_hostname.clear();
    this->_verb.clear();
    this->_parameters.clear();
}

void Message::print(void)
{
    std::vector<std::string> tmp = this->getParameters();

    std::cout << "Src: " << this->getSrc() << std::endl;
    std::cout << "Nick: " << this->getNick() << std::endl;
    std::cout << "User: " << this->getUser() << std::endl;
    std::cout << "hostname: " << this->getHostname() << std::endl;
    std::cout << "Verb: " << this->getVerb() << std::endl;
    std::cout << "Parameters: ";
    for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        std::cout << *it << " | ";
    }
    std::cout << std::endl;
}
