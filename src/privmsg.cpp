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
    std::string                                sendTo = client.getMessage().getParameters()[0];
    std::string                                message = client.getMessage().getParameters()[1];
    std::map<std::string, Channel *>::iterator itChannel = this->_channels.find(sendTo);

    for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
    {
        if (it->second->getNickname() == sendTo)
        {
            it->second->sendMessage(client.getSource() + " PRIVMSG " + it->second->getNickname() + " :" + message);
            return;
        }
    }
    if (itChannel != this->_channels.end())
    {
        if (itChannel->second->lookForClient(&client))
        {
            client.sendMessage(this->_name + ERR_CANNOTSENDTOCHAN(client.getNickname(), sendTo));
            return;
        }
        itChannel->second->sendToAll(client.getSource() + " PRIVMSG " + itChannel->second->getName() + " :" + message);
        return;
    }

    else
    {
        client.sendMessage(this->_name + ERR_NOSUCHNICK(client.getNickname(), sendTo));
    }
}
