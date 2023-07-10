#include "Server.hpp"
#include "Macros.hpp"


Parameters: <channel> <user> *( "," <user> ) [<comment>]
void	Server::kick(Client &client) {
	std::map<std::string, Channel*>::iterator	channelIt;
	std::vector<std::string>					parameters;
	std::set<Client*>							operators;
	std::set<Client*>							clients;
	Message										message;

	if (client.getIsRegistered() == false) {
		client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));
		return;
	}

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 2) {
		client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname()));
		return;
	}

	channelIt = _channels.find(parameters[0]);
	if (channelIt == _channels.end()) {
		client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
		return;
	}

	clients = channelIt->second->getClients();
	operators = channelIt->second->getOperators();
	target = _nicknames.find(target);
	if (clients.find(&client) == clients.end()) {
		client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
		return;
	} else if (operators.find(&client) == operators.end()) {
		client.sendMessage(_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
		return;
	} else if (target == _nicknames.end() || (clients.find(target) == clients.end()) {
		rply(ERR_USERNOTINCHANNEL(client.getNickname(), targetName, _name);
		return;
	} else {
		client.sendMessage("You got kicked lol");
		channel.rmClient(target);
	}
}
