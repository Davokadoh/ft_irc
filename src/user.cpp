#include "Server.hpp"
#include <netdb.h>

void Server::user(Client &client)
{
    if (client.getIsPassOK() == false)
    {
        return;
    }
    if (client.getMessage().getParameters().size() < 4)
    {
        client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
    }
    else if (client.getIsRegistered() == true)
    {
        client.sendMessage(this->_name + ERR_ALREADYREGISTERED(client.getNickname()));
    }
    else
    {
        client.setUsername(client.getMessage().getParameters()[0]);
        client.setRealname(client.getMessage().getParameters()[3]);
        if (client.getNickname() != "*")
        {
            this->registration(client);
        }
    }
}
