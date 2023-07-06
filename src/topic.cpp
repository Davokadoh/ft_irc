#include "Server.hpp"


void	Server::topic(Client &client) {
	Message	message = client.getMessage();
	std::vector<std::string>	parameters;
	std::map<string, Channel*>::iterator	channelIt;
	std::set<Client*>						clients;
	std::set<Client*>						operators;

	parameters = message.getParameters();
	if (parameters.size() < 2) {
		rply(ERR_NOTENOUGHPARAM);
		return;
	}

	channelIt = channels.find();
	if (channelIt == channels.end()) {
		rply(ERR_NOSUCHCHANNEL);
		return;
	}

	clients = channelIt->second.getClients();

	if (clients.find(client.getName()) == clients.end()) {
		rply(ERR_NOTONCHANNEL);
		return;
	}
		
	if (parameters.size() == 2) {
		rply(RPL_TOPIC);
	} else {
		operators = channelIt->second.getOperators();
		if (operators.find(client.getName()) == operators.end()) {
			rply(ERR_CHANOPRIVSNEEDED);
			return;
		}
		channel.setTopic(parameters[2]);
	}
}
