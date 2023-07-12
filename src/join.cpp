#include "Server.hpp"
#include "Macros.hpp"

void	Server::join(Client &client) {
	if (client.getIsRegistered() == false) {
		client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}

	std::string	channel = client.getMessage().getParameters()[0];
	addHashtag(channel);

	std::map<std::string, Channel*>::iterator it = _channels.find(channel);
	if (it == _channels.end()) {
		_channels[channel] = new Channel(channel);
		_channels[channel]->addOperator(client);
		_channels[channel]->addClient(&client);
		_channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
		topic(client);
		names(client);
	}
	else if (it->second->getInviteMode() == true)
	{
		if (it->second->getInviteList().find(&client) == it->second->getInviteList().end() || it->second->getInviteList().empty())
		{
			client.sendMessage(this->_name + ERR_INVITEONLYCHAN(client.getNickname(), channel));
		}
		else
		{
			_channels[channel]->addClient(&client);
			_channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
			topic(client);
			names(client);
		}
	}
	else
	{
		_channels[channel]->addClient(&client);
		_channels[channel]->sendToAll(client.getSource() + " JOIN " + channel);
		topic(client);
		names(client);
	}

	/*
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		std::cout << "Channel: " << it->first << std::endl;
		it->second->printClientList();
	}
	*/
}
