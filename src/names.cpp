#include	"Server.hpp"

//  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
#define RPL_NAMREPLY(client, channel, nick) " 353 " + client + " = " + channel + " " + nick
#define ERR_NOSUCHCHANNEL(client, channel) client + " " + channel  + " :No such channel"
#define RPL_ENDOFNAMES(client, channel) " 366 " + client + " " + channel + " :End of /NAMES list"

void	Server::names(Client &client) {
	std::string channelName = client.getMessage().getParameters()[0];
	std::map<std::string, Channel*>::iterator	channelIt;
	Channel				*channel;
	std::set<Client*>	clients;

	channelIt = _channels.find(channelName);
	if (channelIt == _channels.end()) {
		client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), channelName));
		return;
	}

	channel = channelIt->second;
	clients = channel->getClients();

	for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		client.sendMessage(_name + RPL_NAMREPLY(client.getNickname(), channelName, (*it)->getNickname()));
	}
	client.sendMessage(_name + RPL_ENDOFNAMES(client.getNickname(), channelName));
}

/*
< :server_name 366 jo #pomme :End of /NAMES list.
< :server_name 366 #pomme :End of /NAMES list
*/
