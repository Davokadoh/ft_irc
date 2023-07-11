#include	"Server.hpp"

void	Server::part(Client &client)
{
	if (client.getMessage().getParameters().size() < 2)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname()));
		return;
	}
	std::string	channel = client.getMessage().getParameters[0];

	if (this->_channels.find(channel) == this->_channels.end())
	{
		client.sendMessage(this->_name + ERR_NOSUCHCHANNEL(client.getNickname(), channel));
	}
	else
	{
		for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		{
			if (!it->second->getClients())
		}
	}	
}