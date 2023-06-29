//Command: JOIN
#include "Server.hpp"


void	Server::join(std::string channelName)
{
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channelName);


	//send(); //Send success or error
}

