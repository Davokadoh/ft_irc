#include	"Server.hpp"

void	Server::notice(Client &client)
{
	if (client.getMessage().getParameters().size() < 2)
	{
		return;
	}
	std::string sendTo = client.getMessage().getParameters()[0];
	std::string message = client.getMessage().getParameters()[1];
	std::map<std::string, Channel*>::iterator itChannel = this->_channels.find(sendTo);;

	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == sendTo)
		{
			it->second->sendMessage(client.getSource() + " NOTICE " + it->second->getNickname() + " :" + message);
			return;
		}
	}

	if(itChannel != this->_channels.end())
	{
		itChannel->second->sendToAll(client.getSource() + " NOTICE " + itChannel->second->getName() + " :" + message);
		return;
	}
}
