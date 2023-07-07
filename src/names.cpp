#include	"Server.hpp"

//  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
#define RPL_NAMREPLY(client, channel) " 353 " + client + " = " + channel
#define RPL_ENDOFNAMES(channel) " 366 " + channel + " :End of /NAMES list"


void	Server::names(Client &client) {
	std::string channel = client.getMessage().getParameters()[0];

	client.sendMessage(_name + RPL_NAMREPLY(client.getNickname(), channel));
	client.sendMessage(_name + RPL_ENDOFNAMES(channel));
}
