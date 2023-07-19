#include "Server.hpp"

void Server::part(Client &client)
{
  std::map<std::string, Channel *>::iterator channelIt;
  std::vector<std::string>                   parameters;
  std::string                                channel;
  std::string                                nickname;

  parameters = client.getMessage().getParameters();
  if (parameters.size() < 1)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "PART"));

  channel = parameters[0];
  nickname = client.getNickname();
  channelIt = _channels.find(channel);

  if (channelIt == _channels.end())
    return client.sendMessage(_name + ERR_NOSUCHCHANNEL(nickname, channel));
  if (!channelIt->second->isClient(&client))
    return client.sendMessage(_name + ERR_NOTONCHANNEL(nickname, channel));

  channelIt->second->sendToAll(
    client.getSource() + " PART " + channel + " :" + (parameters.size() > 1 ? parameters[1] : "Leaving"));

  channelIt->second->rmClient(&client);
  if (channelIt->second->getClients().empty())
    _channels.erase(channelIt);
}
