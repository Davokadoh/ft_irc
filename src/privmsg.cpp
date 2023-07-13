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
	std::map<std::string, Channel*>::iterator itChannel = this->_channels.find(sendTo);
	//int			triggerUser = 0;
	//int			triggerChannel = 0;

	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == sendTo)
		{
	//		triggerUser = 1;
			it->second->sendMessage(client.getSource() + " PRIVMSG " + it->second->getNickname() + " :" + message);
		}
	}

	if(itChannel != this->_channels.end())
	{
		itChannel->second->sendToAll(client.getSource() + " PRIVMSG " + itChannel->second->getName() + " :" + message);
	//	triggerChannel = 1;
	}


}
