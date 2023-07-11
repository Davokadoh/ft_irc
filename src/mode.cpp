#include "Server.hpp"
#include "Macros.hpp"

void	Server::mode(Client &client) {
	std::vector<std::string>	parameters;
	Message						message;
	Channel						*channel;
	std::set<Client*>			clients;
	Client						*target;

	if (client.getIsRegistered() == false) {
		client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 1) {
		client.sendMessage(_name + ERR_NEEDMOREPARAMS(clients.getNickname()));
		return;
	}

	if (_channels.find(parameters[0]) == _channels.end()) {
		client.sendMessage(ERR_NOSUCHCHANNEL);
		return;
	}

	channel = _channels.at(parameters[0]);
	clients = channel.getClients();
	if (clients.find(client) == clients.end()) {
		client.sendMessage(NOTONCHANNEL);
		return;
	}

	if (parameters.size() == 1) {
		client.sendMessage("RPL_UMODEIS (221)");
		return;
	}

	if (parameters.at(1).find_first_not_of("+-itokl") != std::string::npos) {
		client.sendMessage(ERR_UNKNOWNMODE);
	}

	if (parameters.size() == 2) {
		if (operators.find(&client) == operators.end()) {
			client.sendMessage(ERR_CHANOPRIVSNEEDED);
			return;
		}
		if (channel.setMode(parameters[1])) {
			client.sendMessage(ERR_UNKNOWNMODE);
		}
		channel.sendToAll(RPL_CHANNELMODEIS);
	} else {
		target == clients.find(parameters[2]);
		target.setMode();
	}
}
