#include	"Server.hpp"

void	Server::invite(Client &client)
{
	if (client.getMessage().getParameters().size() < 2)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));
		return;
	}
	std::map<std::string, Client*>:: iterator clientToInvite = this->_nicknames.find(client.getMessage().getParameters()[0]);
	std::string	channel = client.getMessage().getParameters()[1];
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
	// check droit operateur
	if (!(it->second->lookForClient(clientToInvite->second)))
	{
		client.sendMessage(this->_name + ERR_USERONCHANNEL(nickname, client.getMessage().getParameters()[0], channel));
		return;
	}
	else
	{
		it->second->setInviteList(clientToInvite->second);
		client.sendMessage(client.getSource() + RPL_INVITING(nickname, clientToInvite->second->getNickname(), channel));
		clientToInvite->second->sendMessage(client.getSource() + " INVITE " + clientToInvite->second->getNickname() + " " + channel);
	}
}
