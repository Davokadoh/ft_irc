#include "Macros.hpp"
#include "Server.hpp"

// Parameters: <channel> <user> *( "," <user> ) [<comment>]
void Server::kick(Client &client) {
  std::map<std::string, Channel *>::iterator channelIt;
  std::vector<std::string> parameters;
  Client *target;
  Channel *channel;
  Message message;

  if (client.getIsRegistered() == false) {
    return client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
  }

  message = client.getMessage();
  parameters = message.getParameters();
  if (parameters.size() < 2) {
    client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "KICK"));
    return;
  }

  channelIt = _channels.find(parameters[0]);
  if (channelIt == _channels.end()) {
    client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
    return;
  }

  channel = channelIt->second;
  if (_nicknames.find(std::string(parameters[1])) == _nicknames.end()) {
    return client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[1], channel->getName()));
  }

  target = _nicknames.find(std::string(parameters[1]))->second;
  if (!channel->isClient(&client)) {
    return client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
  } else if (!channel->isOperator(client)) {
    return client.sendMessage(_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
  } else if (!channel->isClient(target)) {
    return client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[1], channel->getName()));
  } else {
    channel->sendToAll(client.getSource() + " KICK " + channel->getName() + " " + target->getNickname());
    channelIt->second->rmClient(target);
  }
}
