#include "Macros.hpp"
#include "Server.hpp"

void Server::names(Client &client)
{
	std::vector<std::string>									 parameters;
	std::map<std::string, Channel *>::iterator channelIt;
	std::set<Client *>												 clients;

	parameters = client.getMessage().getParameters();
	if (parameters.size() < 1)
		return client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "NAMES"));
	channelIt = _channels.find(parameters[0]);
	if (channelIt == _channels.end())
		return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));

	clients = channelIt->second->getClients();
	for (std::set<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
		client.sendMessage(_name + RPL_NAMREPLY(client.getNickname(), parameters[0],
																						(channelIt->second->isOperator(**it) ? "@" : "") + (*it)->getNickname()));

	client.sendMessage(_name + RPL_ENDOFNAMES(client.getNickname(), parameters[0]));
}
