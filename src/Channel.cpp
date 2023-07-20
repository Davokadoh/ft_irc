#include "Channel.hpp"
#include <algorithm>
#include <stdlib.h>

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

std::string Channel::setTopicMode(const bool mode)
{
  if (_topicMode == mode)
  {
    _topicMode = mode;
    return mode ? "+t" : "-t";
  }
  return "";
}

bool Channel::getInviteMode(void) const
{
  return _inviteMode;
}

std::string Channel::setInviteMode(const bool mode)
{
  if (_inviteMode == mode)
  {
    _inviteMode = mode;
    return mode ? "+i" : "-i";
  }
  return "";
}

std::string Channel::setPassword(const bool sign, const std::string &password)
{
  if (password.find(' ') != std::string::npos)
    return "";

  _password = password;
  return sign ? "+k" : "-k";
}

std::string Channel::setLimit(std::vector<std::string> &change, const bool sign, unsigned int limit)
{
  if (sign && limit > 0)
  {
    _limit = limit;
    change.push_back("" << limit);
    return "+l";
  }
  else if (!sign && _limit > 0)
  {
    return "-l";
  }
  else
  {
    return "";
  }
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
