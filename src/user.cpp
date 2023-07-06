#include	"Server.hpp"
#include 	<netdb.h>

#define ERR_NEEDMOREPARAMS(nickname) " 461 " + nickname + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nickname) " 462 " + nickname + " :You may not reregister"


void	Server::user(Client &client)
{
	if (client.getMessage().getParameters().size() < 4)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname()));
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
