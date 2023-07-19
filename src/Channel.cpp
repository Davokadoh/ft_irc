#include "Channel.hpp"
#include <algorithm>

Channel::Channel(void)
{
}

Channel::Channel(const std::string &name)
  : _name(name)
{
}

Channel::Channel(const Channel &rhs)
{
  *this = rhs;
}

Channel &Channel::operator=(const Channel &rhs)
{
  if (this != &rhs)
    this->_clients = rhs._clients;
  return *this;
}

Channel::~Channel(void)
{
}

void Channel::sendToAll(const std::string &msg)
{
  for (std::set<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    (*it)->sendMessage(msg);
}

std::string Channel::getName(void) const
{
  return _name;
}

std::string Channel::getTopic(void) const
{
  return _topic;
}

void Channel::setTopic(const std::string &topic)
{
  _topic = topic;
}

bool Channel::getTopicMode(void) const
{
  return _topicMode;
}

void Channel::setTopicMode(const bool mode)
{
  _topicMode = mode;
}

bool Channel::getInviteMode(void) const
{
  return _inviteMode;
}

void Channel::setInviteMode(const bool mode)
{
  _inviteMode = mode;
}

bool Channel::setPassword(const std::string &password)
{
  if (password.find(' ') != std::string::npos)
    return true;

  _password = password;
  return false;
}

void Channel::setLimit(unsigned int limit)
{
  _limit = limit;
}

std::set<Client *> Channel::getClients(void) const
{
  return _clients;
}

bool Channel::isClient(Client *client) const
{
  return (_clients.find(client) != _clients.end());
}

void Channel::addClient(Client *client)
{
  _clients.insert(client);
}

void Channel::rmClient(Client *client)
{
  _clients.erase(client);
}

bool Channel::isOperator(Client &client) const
{
  return (_operators.find(&client) != _operators.end());
}

void Channel::addOperator(Client &client)
{
  _operators.insert(&client);
}

void Channel::rmOperator(Client &client)
{
  _operators.erase(&client);
}

bool Channel::isInvited(Client &client) const
{
  return (_operators.find(&client) == _operators.end());
}

void Channel::addInvited(Client &client)
{
  _operators.insert(&client);
}

void Channel::rmInvited(Client &client)
{
  _operators.erase(&client);
}

/*
void Channel::setInviteList(Client *client)
{
  _inviteList.insert(client);
}
*/

/*
std::set<Client *> Channel::getInviteList(void) const
{
  return (_inviteList);
}
*/
