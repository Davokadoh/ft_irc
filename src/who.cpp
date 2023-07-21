#include "Server.hpp"

std::string Server::getChannelWith(Client *client)
{
  for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
    if (it->second->isClient(client))
      return it->second->getName();
  return "*";
}

void Server::who(Client &client)
{
  std::vector<std::string> parameters = client.getMessage().getParameters();

  if (parameters.empty())
  {
    for (std::map<std::string, Client *>::iterator clientIt = _nicknames.begin(); clientIt != _nicknames.end(); clientIt++)
    {
      client.sendMessage(
        _name + RPL_WHOREPLY(
                  client.getNickname(),
                  getChannelWith(clientIt->second),
                  clientIt->second->getUsername(),
                  clientIt->second->getIp(),
                  std::string(_name).erase(0),
                  clientIt->first,
                  clientIt->second->getRealname()));
    }
    client.sendMessage(_name + RPL_ENDOFWHO(client.getNickname(), ""));
    return;
  }
  if (_nicknames.find(parameters[0]) != _nicknames.end())
  {
    std::map<std::string, Client *>::iterator clientIt = _nicknames.find(parameters[0]);
    client.sendMessage(
      _name + RPL_WHOREPLY(
                client.getNickname(),
                getChannelWith(clientIt->second),
                clientIt->second->getUsername(),
                clientIt->second->getIp(),
                std::string(_name).erase(0),
                clientIt->first,
                clientIt->second->getRealname()));
    client.sendMessage(_name + RPL_ENDOFWHO(client.getNickname(), parameters[0]));
    return;
  }
  std::map<std::string, Channel *>::iterator channelIt = _channels.find(parameters[0]);
  if (_channels.find(parameters[0]) != _channels.end())
  {
    std::set<Client *> clients = channelIt->second->getClients();
    for (std::set<Client *>::iterator clientIt = clients.begin(); clientIt != clients.end(); ++clientIt)
    {
      client.sendMessage(
        _name + RPL_WHOREPLY(
                  client.getNickname(),
                  getChannelWith(*clientIt),
                  (*clientIt)->getUsername(),
                  (*clientIt)->getIp(),
                  std::string(_name).erase(0),
                  (*clientIt)->getNickname(),
                  (*clientIt)->getRealname()));
    }
    client.sendMessage(_name + RPL_ENDOFWHO(client.getNickname(), parameters[0]));
    return;
  }
  client.sendMessage(_name + RPL_ENDOFWHO(client.getNickname(), parameters[0]));
}
