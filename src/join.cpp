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
	}

	_channels[channel]->addClient(&client);
	client.sendMessage(client.getSource() + " JOIN " + channel);
	//_channels[channel]->sendToAll(&client); //Do this after adding instead, will reply & notice everyone 
	//client.sendMessage(_name + RPL_TOPIC(client.getNickname(), channel));
	//client.sendMessage(_name + RPL_TOPIC(client.getNickname(), channel, _channels.find(channel)->second->getTopic()));
	topic(client);
	names(client);

	/*
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		std::cout << "Channel: " << it->first << std::endl;
		it->second->printClientList();
	}
	*/
}
