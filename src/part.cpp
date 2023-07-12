#include	"Server.hpp"

void	Server::part(Client &client)
{
	if (client.getMessage().getParameters().size() < 1)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname()));
		return;
	}
	std::string	channel = client.getMessage().getParameters()[0];
	std::string nickname = client.getNickname();
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channel);

	if (it == this->_channels.end())
	{
		client.sendMessage(this->_name + ERR_NOSUCHCHANNEL(nickname, channel));
		return;
	}
	if (it->second->lookForClient(&client))
	{
		client.sendMessage(this->_name + ERR_NOTONCHANNEL(nickname, channel));
		return;
	}
	else
	{
		if (client.getMessage().getParameters().size() > 1)
		{
			it->second->sendToAll(client.getSource() + " " + client.getMessage().getVerb() + " "  + channel + " :" + client.getMessage().getParameters()[1]);
		}
		else
		{
			it->second->sendToAll(client.getSource() + " " + client.getMessage().getVerb() + " " + channel + " :Leaving");
		}
		it->second->rmClient(&client);
		if (it->second->getClients().empty())
		{
			this->_channels.erase(it);
		}
	}
}
