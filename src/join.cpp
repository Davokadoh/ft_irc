#include "Macros.hpp"
#include "Server.hpp"

void Server::join(Client &client)
{
  std::string                                channel;
  std::map<std::string, Channel *>::iterator channelIt;

  if (client.getIsRegistered() == false)
    return client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
  if (client.getMessage().getParameters().empty())
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), client.getMessage().getVerb()));

  channel = client.getMessage().getParameters()[0];
  if (channel == "0")
  {
    client.resetMessage();
    partChannels(client);
    return;
  }

  if (channel[0] != '#')
    return client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), channel));

  channelIt = _channels.find(channel);
  if (channelIt == _channels.end())
  {
    _channels[channel] = new Channel(channel);
    _channels[channel]->addOperator(client);
  }
  else if (channelIt->second->getInviteMode() == true)
  {
    if (channelIt->second->isInvited(client))
      channelIt->second->rmInvited(client);
    else
      return client.sendMessage(_name + ERR_INVITEONLYCHAN(client.getNickname(), channel));
  }

  _channels[channel]->addClient(&client);
  _channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
  topic(client);
  names(client);
}
