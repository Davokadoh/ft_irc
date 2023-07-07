#include "Server.hpp"

void	Server::topic(Client &client) {
	std::map<string, Channel*>::iterator	channelIt;
	std::vector<std::string>				parameters;
	std::set<Client*>						clients;
	std::set<Client*>						operators;
	Message									message;

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 1) {
		rply(ERR_NOTENOUGHPARAM);
		return;
	}

	channelIt = channels.find(parameters[0]);
	if (channelIt == channels.end()) {
		rply(ERR_NOSUCHCHANNEL);
		return;
	}

	clients = channelIt->second.getClients();
	if (clients.find(client) == clients.end()) {
		rply(ERR_NOTONCHANNEL);
		return;
	}
		
	if (parameters.size() == 1) {
		rply(RPL_TOPIC);
		return;
	}

	if (channel.getTopicMode()) {
		operators = channelIt->second.getOperators();
		if (operators.find(client) == operators.end()) {
			rply(ERR_CHANOPRIVSNEEDED);
			return;
		}
	}
	channelIt->second.setTopic(parameters[1]);
}
