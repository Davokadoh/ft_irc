#include "Server.hpp"

void	Server::topic(Client &client) {
	std::map<std::string, Channel*>::iterator	channelIt;
	std::vector<std::string>					parameters;
	std::set<Client*>							clients;
	std::set<Client*>							operators;
	Message										message;
	Channel										*channel;

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 1) {
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname()));
		return;
	}

	channelIt = _channels.find(parameters[0]);
	if (channelIt == _channels.end()) {
		client.sendMessage(this->_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
		return;
	}

	channel = channelIt->second;
	clients = channel->getClients();
	if (clients.find(&client) == clients.end()) {
		client.sendMessage(this->_name + ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
		return;
	}
		
	if (parameters.size() == 1) {
		(channel->getTopic().empty())
			? client.sendMessage(client.getSource() + RPL_NOTOPIC(client.getNickname(), channel->getName()))
			: client.sendMessage(client.getSource() + RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
		return;
	}

	if (channel->getTopicMode()) {
		operators = channel->getOperators();
		if (operators.find(&client) == operators.end()) {
			client.sendMessage(this->_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
			return;
		}
	}
	channel->setTopic(parameters[1]);
	client.sendMessage(client.getSource() + RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
}
