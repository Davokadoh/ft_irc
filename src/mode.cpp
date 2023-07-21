#include "Macros.hpp"
#include "Server.hpp"

void Server::mode(Client &client)
{
  std::vector<std::string>                   parameters;
  std::map<std::string, Channel *>::iterator channel;
  std::string                                modeString;
  size_t                                     modeIndex;
  bool                                       sign;

  parameters = client.getMessage().getParameters();
  if (parameters.size() < 1)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  channel = _channels.find(parameters[0]);
  if (channel == _channels.end())
    return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
  else if (!channel->second->isClient(&client))
    return client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), channel->second->getName()));
  else if (parameters.size() == 1)
	return client.sendMessage(client.getSource() + RPL_CHANNELMODEIS(client.getNickname(), channel->second->getName(), channel->second->getModes()));
  else if (!channel->second->isOperator(client))
    return client.sendMessage(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->second->getName()));
  else if (parameters.size() < 2)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  modeString = parameters[1];
  modeIndex = 0;
  for (size_t i = 0; i < modeString.size(); ++i)
    if (modeString[i] == 'o' || modeString[i] == 'k' || modeString[i] == 'l')
      ++modeIndex;
  if (modeIndex > parameters.size() - 2)
    return client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));

  modeIndex = 1;
  sign = true;
  for (size_t index = 0; index < modeString.size(); ++index)
  {
    if (modeString[index] == '+')
      sign = true;
    else if (modeString[index] == '-')
      sign = false;
    else if (modeString[index] == 'i')
      channel->second->setMode(client, i, sign);
    else if (modeString[index] == 't')
      channel->second->setMode(client, t, sign);
    else if (modeString[index] == 'k')
      channel->second->setPassword(client, sign, parameters[++modeIndex]);
    else if (modeString[index] == 'l')
      channel->second->setLimit(client, sign, parameters[++modeIndex]);
    else if (modeString[index] == 'o')
    {
      ++modeIndex;
      channel->second->setOperatorMode(client, sign, parameters[modeIndex], _nicknames.find(parameters[modeIndex])->second);
    }
    else
      client.sendMessage(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
  }
}
