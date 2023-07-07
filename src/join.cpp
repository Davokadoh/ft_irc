//Command: JOIN
#include "Server.hpp"

void	Server::join(Client &client)
{
	if (client.getIsRegistered() == false)
	{
		client.sendMessage(this->_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}
	std::string	channel = client.getMessage().getParameters()[0];
	if (channel[0] != '#')
	{
		channel.insert(0, 1, '#');
	}
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channel);
	if (it == this->_channels.end())
	{
		this->_channels[channel] = new Channel(channel);
	}
	this->_channels[channel]->addClient(&client);
	client.sendMessage(this->_name + RPL_TOPIC(client.getNickname(), channel, this->_channels.find(channel)->second->getTopic()));
	this->names(client);
	
	// just to check
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		std::cout << "Channel: " << it->first << std::endl;
		it->second->printClientList();
	}
	// just to check
	
	//send(); //Send success or error
}
