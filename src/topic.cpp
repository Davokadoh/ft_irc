#include "Server.hpp"

#define ERR_NEEDMOREPARAMS(nickname) " 461 " + nickname + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(client, channel) client + " " + channel  + " :No such channel"
#define ERR_NOTONCHANNEL(client, channel) client + " " + channel + " :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED(client, channel) client + " " + channel + " :You're not channel operator"
#define RPL_NOTOPIC(client, channel) client + " " + channel + " :No topic is set"
#define RPL_TOPIC(client, channel, topic) client + " " + channel + " " + topic

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
		client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname()));
		return;
	}

	channelIt = _channels.find(parameters[0]);
	if (channelIt == _channels.end()) {
		client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
		return;
	}

	channel = channelIt->second;
	clients = channel->getClients();
	if (clients.find(&client) == clients.end()) {
		client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
		return;
	}
		
	if (parameters.size() == 1) {
		(channel->getTopic().empty())
			? client.sendMessage(RPL_NOTOPIC(client.getNickname(), channel->getName()))
			: client.sendMessage(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
		return;
	}

	if (channel->getTopicMode()) {
		operators = channel->getOperators();
		if (operators.find(&client) == operators.end()) {
			client.sendMessage(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
			return;
		}
	}
	channel->setTopic(parameters[1]);
	client.sendMessage(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
}
