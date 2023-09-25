#include "Server.hpp"

void Server::part(Client &client)
{
	std::map<std::string, Channel *>::iterator channelIt;
	std::vector<std::string>									 parameters;

	parameters = client.getMessage().getParameters();
	if (parameters.size() < 1)
		return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname(), "PART"));

	parameters[0] = parameters[0];
	channelIt = _channels.find(parameters[0]);

	if (channelIt == _channels.end())
		return client.sendMessage(_name + ERR_NOSUCHCHANNEL(client.getNickname(), parameters[0]));
	if (!channelIt->second->isClient(client))
		return client.sendMessage(_name + ERR_NOTONCHANNEL(client.getNickname(), parameters[0]));

	channelIt->second->sendToAll(
		client.getSource() + " PART " + parameters[0] + " :" + (parameters.size() > 1 ? parameters[1] : "Leaving"), NULL);

	channelIt->second->rmClient(client);
	channelIt->second->rmOperator(client);
	if (channelIt->second->isEmpty())
		_channels.erase(channelIt);
}
