#include "Macros.hpp"
#include "Server.hpp"

void Server::mode(Client &client) {
  std::vector<std::string> parameters;
  std::string modeString;
  Channel *channel;
  Client *target;
  size_t modeArgIndex;

  if (!client.getIsRegistered())
    return client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));

  parameters = client.getMessage().getParameters();
  if (parameters.size() < 1)
    return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname()));
  else if (_channels.find(parameters[0]) == _channels.end())
    return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));

  channel = _channels.at(parameters[0]);
  if (!channel->isClient(&client))
    return client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
  else if (parameters.size() == 1)
    return client.sendMessage("RPL_CHANNELMODEIS");
  else if (channel->isOperator(client))
    return client.sendMessage(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));

  modeString = parameters.at(0);
  modeArgIndex = 0;
  while (modeString.find_first_of("okl") != std::string::npos) {
    ++modeArgIndex;
    modeString += modeString.find_first_of("okl");
  }
  if (modeArgIndex < parameters.size() - 2)
    return client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname()));
  modeString = parameters.at(0);

  bool sign = true;
  for (size_t i = 0; i < modeString.size(); ++i) {
    if (modeString[i] == '+') {
      sign = true;
    } else if (modeString[i] == '-') {
      sign = false;
    } else if (modeString[i] == 'i') {
      channel->setInviteMode(sign);
    } else if (modeString[i] == 't') {
      channel->setTopicMode(sign);
    } else if (modeString[i] == 'k') {
      if (channel->setPassword(sign ? parameters[++modeArgIndex] : "")) { // ERR_INVALIDKEY
        client.sendMessage("KEY ERROR");
      }
    } else if (modeString[i] == 'l') {
      channel->setLimit(sign ? std::atoi(parameters[++modeArgIndex].c_str()) : 0); // ERR_INVALIDMODEPARAM
    } else if (modeString[i] == 'o') {
      if (_nicknames.find(parameters[++modeArgIndex]) == _nicknames.end()) {
        client.sendMessage("ERR_USERNOTINCHANNEL");
        continue;
      }
      target = _nicknames[parameters[modeArgIndex]];
      if (channel->isClient(target)) {
        client.sendMessage("ERR_USERNOTINCHANNEL");
        continue;
      }
      (sign) ? channel->addOperator(*target) : channel->rmOperator(*target);
    } else {
      client.sendMessage("ERR_UMODEUNKNOWNFLAG");
    }
  }
}
