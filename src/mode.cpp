#include "Server.hpp"
#include "Macros.hpp"

void	Server::mode(Client &client) {
	std::vector<std::string>	parameters;
	Message						message;
	Channel						*channel;
	std::set<Client*>			chClients;
	Client						*target;

	if (client.getIsRegistered() == false) {
		client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 1) {
		client.sendMessage(_name + ERR_NEEDMOREPARAMS(chClients.getNickname()));
		return;
	}

	if (_channels.find(parameters[0]) == _channels.end()) {
		client.sendMessage(ERR_NOSUCHCHANNEL);
		return;
	}

	channel = _channels.at(parameters[0]);
	chClients = channel.getClients();
	if (chClients.find(client) == chClients.end()) {
		client.sendMessage(URNOTONCHANNEL);
		return;
	}

	if (parameters.size() == 1) {
		client.sendMessage(RPL_CHANNELMODEIS);
		return;
	}

	if (operators.find(&client) == operators.end()) {
		client.sendMessage(ERR_CHANOPRIVSNEEDED);
		return;
	}

	std::string &mode = parameters.at(1);
	if (mode.find_first_not_of("+-itokl") != std::string::npos) {
		client.sendMessage(ERR_UMODEUNKNOWNFLAG);
	}

	bool	sign = true;
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it) {
		if (it == '+') {
			sign = true;
		} else if (it == '-') {
			sign = false;
		} else if (it == 'i') {
			channel.setInviteMode(sign);
		} else if (it == 't') {
			channel.setTopicMode(sign);
		} else if (it == 'k') {
			if (channel.setPassword(sign ? parameters.next() : "")) {
				client.sendMessage(ERR_INVALIDKEY);
			}
		} else if (it == 'l') {
			channel.setLimit(sign ? parameters.next() : "");
		} else if (it == 'o') {
			chClients.find(parameters.next());
			if (chClients.find(parameters.next() == chClients.end()) {
				client.sendMessage(ERR_USERNOTINCHANNEL);
				continue;
			}
			target = chClient.at(parameters[0]);
			
			if (sign) {
				channel.addOperator(target);
			} else {
				channel.rmOperator(target);
			}
		}
	}

	channel.sendToAll(RPL_CHANNELMODEIS);
}
