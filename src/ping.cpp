#include	"Server.hpp"

void	Server::ping(Client &client)
{
	client.sendMessage(this->_name + " PONG " + this->_name + " " + client.getMessage().getParameters()[0]);
}
