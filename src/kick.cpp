#include "Server.hpp"
#include "Macros.hpp"

//Parameters: <channel> <user> *( "," <user> ) [<comment>]
void	Server::kick(Client &client) {
	std::map<std::string, Channel*>::iterator	channelIt;
	std::vector<std::string>					parameters;
	std::set<Client*>							operators;
	std::set<Client*>							clients;
	Client										*target;
	Channel										*channel;
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

	channel = channelIt->second;
	clients = channel->getClients();
	operators = channel->getOperators();
	if (_nicknames.find(std::string(parameters[1])) == _nicknames.end()) {
		client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[1], channel->getName()));
		return;
	}
		
	target = _nicknames.find(std::string(parameters[1]))->second;
	if (clients.find(&client) == clients.end()) {
		client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
		return;
	} else if (operators.find(&client) == operators.end()) {
		client.sendMessage(_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
		return;
	} else if (clients.find(target) == clients.end()) {
		client.sendMessage(_name + ERR_USERNOTINCHANNEL(client.getNickname(), parameters[1], channel->getName()));
		return;
	} else {
		channel->sendToAll(client.getSource() + " KICK " + channel->getName() + " " + target->getNickname());
		channelIt->second->rmClient(target);
	}
}
