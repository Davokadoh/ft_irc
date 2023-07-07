#include	"Server.hpp"

void	Server::names(Client &client)
{
	std::string channel = client.getMessage().getParameters()[0];

	client.sendMessage(this->_name + RPL_NAMREPLY(channel) + client.getNickname()); // a modifier avec tous les client co au channel
	client.sendMessage(this->_name + RPL_ENDOFNAMES(channel));
}
