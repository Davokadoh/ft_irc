#include "Macros.hpp"
#include "Server.hpp"

void Server::kick(Client &client)
{
  std::vector<std::string>                   parameters;
  std::map<std::string, Channel *>::iterator channel;
  std::map<std::string, Client *>::iterator  target;

  parameters = client.getMessage().getParameters();
  if (parameters.size() < 2)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "KICK"));

  target = _nicknames.find(parameters[1]);
  channel = _channels.find(parameters[0]);
  if (channel == _channels.end())
    return client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
  else if (!channel->second->isClient(&client))
    return client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), channel->second->getName()));
  else if (!channel->second->isOperator(client))
    return client.sendMessage(_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->second->getName()));
  else if (!channel->second->isClient(target->second))
    return client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[1], channel->second->getName()));

  channel->second->sendToAll(client.getSource() + " KICK " + channel->second->getName() + " " + target->second->getNickname());
  channel->second->rmClient(target->second);
}
