//Command: JOIN
#include "Server.hpp"


void	Server::join(Client &client)
{
	// need to check if cmd can be excecuted
	std::string	channel = client.getMessage().getParameters()[0];
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channel);
	if (it == this->_channels.end())
	{
		this->_channels[channel] = new Channel;
	}
	this->_channels[channel]->addClient(&client);
	
	// just to check
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		std::cout << "Channel: " << it->first << std::endl;
		it->second->printClientList();
	}
	// just to check
	
	//send(); //Send success or error
}
