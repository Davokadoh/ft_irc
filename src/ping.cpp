#include "Server.hpp"

void Server::ping(Client &client)
{
	if (client.getMessage().getParameters().empty())
		client.sendMessage(this->_name + " PONG " + this->_name);
	else
		client.sendMessage(this->_name + " PONG " + this->_name + " " + client.getMessage().getParameters()[0]);
}
