//Command: JOIN
#include "Server.hpp"

#define RPL_TOPIC(nickname, channel) " 332 " + nickname + " " + channel + " :No topic"
#define ERR_NOTREGISTERED(nickname) " 451 " + nickname + " :You have not registered"

void	Server::join(Client &client) {
	if (client.getIsRegistered() == false) {
		client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}

	std::string	channel = client.getMessage().getParameters()[0];
	if (channel[0] != '#') {
		channel.insert(0, 1, '#');
	}

	std::map<std::string, Channel*>::iterator it = _channels.find(channel);
	if (it == _channels.end()) {
		_channels[channel] = new Channel(channel);
	}

	//_channels[channel]->sendToAll(&client);
	_channels[channel]->addClient(&client);
	client.sendMessage(client.getSource() + " JOIN #" + channel);
	client.sendMessage(_name + RPL_TOPIC(client.getNickname(), channel));
	names(client);
}
