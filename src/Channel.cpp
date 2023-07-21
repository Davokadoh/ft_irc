#include "Server.hpp"
#include "Channel.hpp"
#include "Macros.hpp"

const std::string Channel::_modesStr[4] = {"i", "t", "k", "l"};

Channel::Channel(void)
{
}

Channel::Channel(const std::string &name, const std::string &serverName)
  : _name(name), _serverName(serverName)
{
	for (int i = 0; i < 4; ++i)
		_modes[i] = false;
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

void Channel::sendToAll(const std::string &msg, Client *exception)
{
  std::set<Client *> copy = _clients;
  copy.erase(exception);
  for (std::set<Client *>::iterator it = copy.begin(); it != copy.end(); ++it)
    (*it)->sendMessage(msg);
}

std::string Channel::getName(void) const
{
  return _name;
}

std::string /*&*/Channel::getModes(void) const
{
  std::string modesStr = "";

  modesStr.append(_modes[0] ? "i" : "");
  modesStr.append(_modes[1] ? "k" : "");
  modesStr.append(_modes[2] ? "l" : "");
  modesStr.append(_modes[3] ? "t" : "");
  modesStr.append(_modes[1] ? " " + _password : "");
  modesStr.append(_modes[2] ? " " + intToString(_limit) : "");
  modesStr.insert(0, !modesStr.empty() ? "+" : "");
  return modesStr;
}

bool Channel::getMode(Mode mode) const
{
	return _modes[mode];
}

void Channel::setMode(Client &client, Mode mode, bool sign)
{
  if (_modes[mode] == sign)
    return;
  _modes[mode] = sign;
  sendToAll(client.getSource() + std::string(" MODE ") + _name + (sign ? std::string(" +") : std::string(" -")) + _modesStr[mode], NULL);
}

std::string Channel::getTopic(void) const
{
  return _topic;
}

void Channel::setTopic(const std::string &topic)
{
  _topic = topic;
}

void Channel::setPassword(Client &client, const bool sign, const std::string &password)
{
  if (password.find(' ') != std::string::npos)
    return client.sendMessage(_serverName + ERR_INVALIDKEY(client.getNickname(), _name));

  _password = password;
  _modes[k] = sign;
  sendToAll(client.getSource() + " MODE " + _name + (sign ? " +k " : " -k ") + password, NULL);
}

const std::string &Channel::getPassword(void) const
{
	return _password;
}

void Channel::setLimit(Client &client, const bool sign, const std::string &limitStr)
{
  int limit = std::atoi(limitStr.c_str());
  if (limit <= 0)
    return;
  else if (!sign)
    return sendToAll(client.getSource() + " MODE " + _name + " -l ", NULL);

  _limit = limit;
  _modes[l] = sign;
  sendToAll(client.getSource() + " MODE " + _name + " +l " + limitStr, NULL);
}

void Channel::setOperatorMode(Client &client, const bool sign, const std::string &nick, Client *target)
{
  if (!isClient(target))
  {
    return client.sendMessage(_serverName + ERR_USERNOTINCHANNEL(client.getNickname(), nick, _name));
  }
  else if (sign && !isOperator(*target))
  {
    addOperator(*target);
    return sendToAll(client.getSource() + " MODE " + _name + " +o " + nick, NULL);
  }
  else if (!sign && isOperator(*target))
  {
    rmOperator(*target);
    return sendToAll(client.getSource() + " MODE " + _name + " -o " + nick, NULL);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////

bool Channel::isEmpty(void) const
{
  return _clients.size();
}

const std::set<Client *> &Channel::getClients(void) const
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
