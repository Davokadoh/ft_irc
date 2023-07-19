#include "Macros.hpp"
#include "Server.hpp"

void Server::names(Client &client)
{
    std::string channelName = client.getMessage().getParameters()[0]; // Need to check param.size()
    std::map<std::string, Channel *>::iterator channelIt;
    Channel                                   *channel;
    std::set<Client *>                         clients;

    addHashtag(channelName);
    channelIt = _channels.find(channelName);
    if (channelIt == _channels.end())
    {
        client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), channelName));
        return;
    }

    channel = channelIt->second;
    clients = channel->getClients();

    for (std::set<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        client.sendMessage(_name + RPL_NAMREPLY(client.getNickname(), channelName, (*it)->getNickname()));
    }

    client.sendMessage(_name + RPL_ENDOFNAMES(client.getNickname(), channelName));

    // for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
    // {
    // 	std::cout << "Channel: " << it->second->getName() << std::endl;
    // 	it->second->printClientList();
    // 	std::cout << std::endl;
    // }
}

/*
< :server_name 366 jo #pomme :End of /NAMES list.
< :server_name 366 #pomme :End of /NAMES list
*/
