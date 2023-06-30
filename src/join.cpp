//Command: JOIN
#include "Server.hpp"


void	Server::join(std::string channelName, Client *client)
{
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channelName);
	if (it == this->_channels.end())
	{
		this->_channels[channelName] = new Channel;
	}
	this->_channels[channelName]->addClient(client);
	
	// just to check
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		std::cout << "Channel: " << it->first << std::endl;
		it->second->printClientList();
	}
	// just to check
	
	//send(); //Send success or error
}
