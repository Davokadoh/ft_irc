#include "Macros.hpp"
#include "Server.hpp"
#include <string>

void Server::mode(Client &client)
{
  std::vector<std::string>                   parameters;
  std::string                                modeString;
  std::map<std::string, Channel *>::iterator channel;
  Client                                    *target;
  size_t                                     modeIndex;

  parameters = client.getMessage().getParameters();
  if (parameters.size() < 1)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  channel = _channels.find(parameters[0]);
  if (channel == _channels.end())
    return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
  else if (!channel->second->isClient(&client))
    return client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), channel->second->getName()));
  else if (parameters.size() == 1)
    return client.sendMessage(_name + " " + channel->second->getName());
  else if (!channel->second->isOperator(client))
    return client.sendMessage(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->second->getName()));
  else if (parameters.size() < 2)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  modeString = parameters[1];
  modeIndex = 0;
  for (size_t i = 0; i < modeString.size(); ++i)
    if (modeString[i] == 'o' || modeString[i] == 'k' || modeString[i] == 'l')
      ++modeIndex;
  std::cout << "ai: " << modeIndex << std::endl;
  if (modeIndex < parameters.size() - 2)
    return client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  int         j = 0;
  bool        sign = true;
  std::string change;
  for (size_t i = 0; i < modeString.size(); ++i)
  {
    if (modeString[i] == '+')
      sign = true;
    else if (modeString[i] == '-')
      sign = false;
    else if (modeString[i] == 'i')
      change.append((channel->second->setInviteMode(sign)) ? (sign + "i") : "");
    else if (modeString[i] == 't')
      channel->second->setTopicMode(sign);
    else if (modeString[i] == 'k')
    {
      if (channel->second->setPassword(sign ? parameters[++modeIndex] : ""))
        client.sendMessage("ERR_INVALIDKEY");
      else
        client.sendMessage(client.getSource() + " MODE " + channel->second->getName() + " +k " + parameters[modeIndex]);
    }
    else if (modeString[i] == 'l')
      channel->second->setLimit(sign ? std::atoi(parameters[++modeIndex].c_str()) : 0); // ERR_INVALIDMODEPARAM
    else if (modeString[i] == 'o')
    {
      if (_nicknames.find(parameters[++modeIndex]) == _nicknames.end())
      {
        client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[modeIndex], channel->second->getName()));
        continue;
      }
      target = _nicknames[parameters[modeIndex]];
      if (channel->second->isClient(target))
      {
        client.sendMessage("ERR_USERNOTINCHANNEL");
        continue;
      }
      (sign) ? channel->second->addOperator(*target) : channel->second->rmOperator(*target);
    }
    else
      client.sendMessage("ERR_UMODEUNKNOWNFLAG");
  }
  client.sendMessage(change);
}
