#include "Server.hpp"

void Server::topic(Client &client)
{
	std::map<std::string, Channel *>::iterator channelIt;
	std::vector<std::string>									 parameters;
	std::set<Client *>												 clients;
	std::set<Client *>												 operators;
	Message																		 message;
	Channel																		*channel;

	message = client.getMessage();
	parameters = message.getParameters();
	if (parameters.size() < 1)
		return client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), "TOPIC"));

	channelIt = _channels.find(parameters[0]);
	if (channelIt == _channels.end())
		return client.sendMessage(this->_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));

	channel = channelIt->second;
	if (!channel->isClient(client))
		return client.sendMessage(this->_name + ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));

	if (parameters.size() == 1)
		return client.sendMessage(_name +
															(channel->getTopic().empty()
																 ? RPL_NOTOPIC(client.getNickname(), channel->getName())
																 : RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic())));

	if (channel->getMode(t) && !channel->isOperator(client))
		return client.sendMessage(this->_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
	channel->setTopic(parameters[1]);
	channel->sendToAll(_name + RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()), NULL);
}
