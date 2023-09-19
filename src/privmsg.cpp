#include "Server.hpp"

void Server::privmsg(Client &client)
{
	if (client.getMessage().getParameters().empty())
	{
		return client.sendMessage(this->_name + ERR_NORECIPIENT(client.getNickname(), client.getMessage().getVerb()));
	}
	if (client.getMessage().getParameters().size() < 2)
	{
		return client.sendMessage(this->_name + ERR_NOTEXTTOSEND(client.getNickname()));
	}

	std::string message = client.getMessage().getParameters().back();

	for (unsigned int i = 0; i < client.getMessage().getParameters().size() - 1; ++i)
	{
		std::string																 sendTo = client.getMessage().getParameters()[i];
		std::map<std::string, Channel *>::iterator itChannel = this->_channels.find(sendTo);
		std::map<std::string, Client *>::iterator	 itClient = this->_nicknames.find(sendTo);

		if (itClient != this->_nicknames.end())
		{
			itClient->second->sendMessage(client.getSource() + " PRIVMSG " + itClient->second->getNickname() + " :" + message);
		}
		else if (itChannel != this->_channels.end())
		{
			if (!itChannel->second->isClient(&client))
			{
				client.sendMessage(this->_name + ERR_CANNOTSENDTOCHAN(client.getNickname(), sendTo));
			}
			else
			{
				itChannel->second->sendToAll(client.getSource() + " PRIVMSG " + itChannel->second->getName() + " :" + message, &client);
			}
		}
		else
		{
			client.sendMessage(this->_name + ERR_NOSUCHNICK(client.getNickname(), sendTo));
		}
	}
}
