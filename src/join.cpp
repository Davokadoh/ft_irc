#include "Macros.hpp"
#include "Server.hpp"

void Server::join(Client &client)
{
    if (client.getIsRegistered() == false)
    {
        client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
        return;
    }
    if (client.getMessage().getParameters().empty())
    {
        client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), client.getMessage().getVerb()));
        return;
    }
    std::string channel = client.getMessage().getParameters()[0];
    if (channel == "0")
    {
        client.resetMessage();
        this->partChannels(client);
        return;
    }
    addHashtag(channel);

    std::map<std::string, Channel *>::iterator it = _channels.find(channel);
    if (it == _channels.end())
    {
        _channels[channel] = new Channel(channel);
        _channels[channel]->addOperator(client);
        _channels[channel]->addClient(&client);
        _channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
        topic(client);
        names(client);
    }
    else if (it->second->getInviteMode() == true)
    {
        if (!it->second->clientOnInvite(&client))
        {
            client.sendMessage(this->_name + ERR_INVITEONLYCHAN(client.getNickname(), channel));
        }
        else
        {
            _channels[channel]->addClient(&client);
            _channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
            topic(client);
            names(client);
            it->second->rmClientFromInvite(&client);
        }
    }
    else
    {
        _channels[channel]->addClient(&client);
        _channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
        topic(client);
        names(client);
    }

    /*
    for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
    {
            std::cout << "Channel: " << it->first << std::endl;
            it->second->printClientList();
    }
    */
}
