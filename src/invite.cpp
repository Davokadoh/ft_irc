#include "Macros.hpp"
#include "Server.hpp"

void Server::invite(Client &client)
{
	std::vector<std::string>									 parameters;
	std::map<std::string, Channel *>::iterator channel;
	std::map<std::string, Client *>::iterator	 target;

	parameters = client.getMessage().getParameters();
	if (parameters.size() < 2)
		return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));

	target = _nicknames.find(parameters[0]);
	channel = _channels.find(parameters[1]);
	if (channel == _channels.end())
		return client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[1]));
	else if (!channel->second->isClient(client))
		return client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), parameters[1]));
	else if (channel->second->isClient(*target->second))
		return client.sendMessage(_name + ERR_USERONCHANNEL(client.getNickname(), parameters[0], parameters[1]));
	else if (channel->second->getMode(i) && !channel->second->isOperator(*target->second))
		return client.sendMessage(_name + ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->second->getName()));

	channel->second->addInvited(*target->second);
	client.sendMessage(_name + RPL_INVITING(client.getNickname(), target->second->getNickname(), parameters[1]));
	target->second->sendMessage(client.getSource() + " INVITE " + target->second->getNickname() + " " + parameters[1]);
}
