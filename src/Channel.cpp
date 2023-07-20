#include "Channel.hpp"
#include "Macros.hpp"
#include <algorithm>
#include <stdlib.h>

Channel::Channel(void)
{
}

Channel::Channel(const std::string &name, const std::string &serverName)
  : _name(name), _serverName(serverName)
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

//< :jo!~jojo@185.25.ovp.mqm MODE #pomme +t
void Channel::setTopicMode(Client &client, const bool mode)
{
  if (_topicMode == mode)
    return;
  _topicMode = mode;
  client.sendMessage((mode ? "+t" : "-t");
}

bool Channel::getInviteMode(void) const
{
  return _inviteMode;
}

void Channel::setInviteMode(Client &client, const bool mode)
{
  if (_inviteMode == mode)
    return;
  _inviteMode = mode;
  client.sendMessage(client.getSource() + " MODE " + _name + (mode ? " +i" : " -i"));
}

void Channel::setPassword(Client &client, const bool mode, const std::string &password)
{
  if (password.find(' ') != std::string::npos)
    return client.sendMessage(_serverName + ERR_NOTONCHANNEL(client.getNickname(), _name)); // Need macro KEY

  _password = password;
  client.sendMessage(client.getSource() + " MODE " + _name + (mode ? " +k " : " -k ") + password);
}

//< :jo!~jojo@185.25.ovp.mqm MODE #pomme +l 32
void Channel::setLimit(Client &client, const bool mode, const std::string &limitStr)
{
  int limit = std::atoi(limitStr.c_str());
  if (limit <= 0)
    return;
  else if (!mode)
    return client.sendMessage(client.getSource() + " MODE " + _name + " -l ");

  _limit = limit;
  client.sendMessage(client.getSource() + " MODE " + _name + " +l " + limitStr);
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
  //":irc-us1.alphachat.net 461 jo MODE :Not enough parameters"

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
