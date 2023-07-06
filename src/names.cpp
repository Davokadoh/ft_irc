#include	"Server.hpp"

#define RPL_NAMREPLY(channel) " 353 " + channel + " = "
#define RPL_ENDOFNAMES(channel) " 366 " + channel + " :End of /NAMES list"


void	Server::names(Client &client)
{
	std::string channel = client.getMessage().getParameters()[0];

	client.sendMessage(this->_name + RPL_NAMREPLY(channel) + client.getNickname()); // a modifier avec tous les client co au channel
	client.sendMessage(this->_name + RPL_ENDOFNAMES(channel));
}
