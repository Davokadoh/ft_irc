#include "Macros.hpp"
#include "Server.hpp"

void Server::names(Client &client)
{
  std::string                                channelName = client.getMessage().getParameters()[0]; // Need to check param.size()
  std::map<std::string, Channel *>::iterator channelIt;
  Channel                                   *channel;
  std::set<Client *>                         clients;

  channelIt = _channels.find(channelName);
  if (channelIt == _channels.end())
    return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), channelName));

  channel = channelIt->second;
  clients = channel->getClients();

  for (std::set<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
    client.sendMessage(_name + RPL_NAMREPLY(client.getNickname(), channelName, (*it)->getNickname()));

  client.sendMessage(_name + RPL_ENDOFNAMES(client.getNickname(), channelName));
}
