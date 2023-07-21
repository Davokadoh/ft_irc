#include "Macros.hpp"
#include "Server.hpp"
#include <utility>

void Server::join(Client &client)
{
  std::vector<std::string>                   parameters;
  std::map<std::string, Channel *>::iterator channelIt;

  if (client.getIsRegistered() == false)
    return client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));

  parameters = client.getMessage().getParameters();
  if (parameters.empty())
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "JOIN"));

  if (parameters[0] == "0")
  {
    client.resetMessage();
    partChannels(client);
    return;
  }

  if (parameters[0][0] != '#')
    return client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));

  if (parameters[0].find_first_not_of(VALID_CHARS, 1) != std::string::npos)
    return client.sendMessage(_name + ERR_BADCHANMASK(parameters[0]));

  channelIt = _channels.find(parameters[0]);
  if (channelIt == _channels.end())
  {
    channelIt = _channels.insert(std::make_pair(parameters[0], new Channel(parameters[0], _name))).first;
    channelIt->second->addOperator(client);
  }
  if (channelIt->second->getMode(i) == true)
  {
    if (channelIt->second->isInvited(client))
      channelIt->second->rmInvited(client);
    else
      return client.sendMessage(_name + ERR_INVITEONLYCHAN(client.getNickname(), parameters[0]));
  }
  if (channelIt->second->getMode(k) == true)
  {
    if (parameters.size() < 2 || parameters[1] != channelIt->second->getPassword())
      return client.sendMessage(_name + ERR_BADCHANNELKEY(client.getNickname(), parameters[0]));
  }
  if (channelIt->second->getMode(l) == true)
  {
    if (channelIt->second->getClients().size() >= channelIt->second->getLimit())
      return client.sendMessage(_name + ERR_CHANNELISFULL(client.getNickname(), parameters[0]));
  }

  channelIt->second->addClient(&client);
  channelIt->second->sendToAll(client.getSource() + " JOIN " + parameters[0], NULL);
  std::string copy(parameters[0]);
  client.resetMessage();
  client.setMessage("JOIN", copy);
  topic(client);
  names(client);
}
