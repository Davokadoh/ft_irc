#include "Server.hpp"

void Server::privmsg(Client &client)
{
  if (client.getMessage().getParameters().empty())
  {
    client.sendMessage(this->_name + ERR_NORECIPIENT(client.getNickname(), client.getMessage().getVerb()));
    return;
  }
  if (client.getMessage().getParameters().size() < 2)
  {
    client.sendMessage(this->_name + ERR_NOTEXTTOSEND(client.getNickname()));
    return;
  }
  std::string                                message = client.getMessage().getParameters().back();

  for (unsigned int i = 0; i < client.getMessage().getParameters().size() -1; ++i)
  {
    std::string                                sendTo = client.getMessage().getParameters()[i];
    std::map<std::string, Channel *>::iterator itChannel = this->_channels.find(sendTo);
    int found = 0;

    for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
      if (it->second->getNickname() == sendTo)
      {
        it->second->sendMessage(client.getSource() + " PRIVMSG " + it->second->getNickname() + " :" + message);
        found = 1;
      }
    }
    if (found == 1)
    {
      continue;
    }
    if (itChannel != this->_channels.end())
    {
      if (!itChannel->second->isClient(&client))
      {
        client.sendMessage(this->_name + ERR_CANNOTSENDTOCHAN(client.getNickname(), sendTo));
        continue;
      }
      else
      {
        itChannel->second->sendToAll(client.getSource() + " PRIVMSG " + itChannel->second->getName() + " :" + message, &client);
        continue;
      }
    }
    else
    {
      client.sendMessage(this->_name + ERR_NOSUCHNICK(client.getNickname(), sendTo));
    }
  }
}
