#include	"Server.hpp"

void	Server::privmsg(Client &client)
{
	if (client.getMessage().getParameters().size() < 2)
	{
		client.sendMessage(this->_name + ERR_NOTEXTTOSEND(client.getNickname()));
		return;
	}
	std::string sendTo = client.getMessage().getParameters()[0];
	std::string message = client.getMessage().getParameters()[1];
	//int			triggerUser = 0;
	//int			triggerChannel = 0;

	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == sendTo)
		{
	//		triggerUser = 1;
			it->second->sendMessage(client.getSource() + " PRIVMSG " + client.getNickname() + " " + message);
		}
	}

	if(this->_channels.find(sendTo) != this->_channels.end())
	{
	//	triggerChannel = 1;
	}


}
