#include	"Server.hpp"

void	Server::notice(Client &client)
{
	if (client.getMessage().getParameters().empty())
	{
		return; 
	}
	if (client.getMessage().getParameters().size() < 2)
	{
		return;
	}
	std::string sendTo = client.getMessage().getParameters()[0];
	std::string message = client.getMessage().getParameters()[1];
	std::map<std::string, Channel*>::iterator itChannel = this->_channels.find(sendTo);
	int			triggerOpe = 0;

	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == sendTo)
		{
			it->second->sendMessage(client.getSource() + " NOTICE " + it->second->getNickname() + " :" + message);
		}
	}
	if (sendTo.find("@") == 0)
	{
		triggerOpe++;
		sendTo.erase(0, 1);
	}

	if(itChannel != this->_channels.end())
	{
		if (triggerOpe != 0)
		{
			std::cout << "CHECK OPERATOR" << std::endl;
			/*if (!itChannel->second->isOpe(client))
			{
				client.sendMessage(this->_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), sendTo));
				return;
			}
			else
			{
				sendToChannelOpe(message);
			}*/
		}
		itChannel->second->sendToAll(client.getSource() + " NOTICE " + itChannel->second->getName() + " :" + message);
	}
}
