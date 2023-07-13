#include "Server.hpp"
#include "Macros.hpp"

void	Server::mode(Client &client) {
	std::vector<std::string>	parameters;
	std::string					modeString;
	Channel						*channel;
	Client						*target;
	size_t						modeArgIndex;

	if (!client.getIsRegistered())
		return client.sendMessage(_name + ERR_NOTREGISTERED(client.getNickname()));

	parameters = client.getMessage().getParameters();
	if (parameters.size() < 1)
		return client.sendMessage(_name + ERR_NEEDMOREPARAMS(client.getNickname()));
	else if (_channels.find(parameters[0]) == _channels.end())
		return client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), channel->getName()));

	channel = _channels.at(parameters[0]);
	if (!channel->isClient(&client))
		return client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), channel->getName()));
	else if (parameters.size() == 1)
		return client.sendMessage("RPL_CHANNELMODEIS");
	else if (channel->isOperator(client))
		return client.sendMessage(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));

	modeString = parameters.at(0);
	modeArgIndex = 0;
	while (modeString.find_first_of("okl") != modeString.end()) {
		++modeArgIndex;
		modeString = *modeString.find_first_of("okl");
	}
	if (modeArgIndex < parameters.size() - 2)
		return client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname()));
	modeString = parameters.at(0);

	bool	sign = true;
	for (size_t i = 0; i < modeString.size(); ++i) {
		if (modeString[i] == '+') {
			sign = true;
		} else if (modeString[i] == '-') {
			sign = false;
		} else if (modeString[i] == 'i') {
			channel.setInviteMode(sign);
		} else if (modeString[i] == 't') {
			channel.setTopicMode(sign);
		} else if (modeString[i] == 'k') {
			(++modeArgIndex > parameters.size() - 2)
			? channel.setPassword(sign ? parameters[++modeArgIndex] : ""); //ERR_INVALIDKEY
			: client.sendMessage("KEY ERROR");
		} else if (modeString[i] == 'l') {
			channel.setLimit(sign ? std::atoi(parameters[++modeArgIndex]) : 0); //ERR_INVALIDMODEPARAM
		} else if (modeString[i] == 'o') {
			if (channel.isClient(parameters[++modeArgIndex]))
				continue client.sendMessage(ERR_USERNOTINCHANNEL);
			target = channel.getClients().at(parameters[modeArgIndex]);
			(sign) ? channel.addOperator(target) : channel.rmOperator(target);
		} else {
			client.sendMessage(ERR_UMODEUNKNOWNFLAG);
		}
	}

	//In each function call that succeeds, call channel.sendToAll(RPL_CHANNELMODEIS);
}
















	for (size_t i = 0; i < modeString.size(); ++i) {
		if (modeString[i] == '+') {
			sign = true;
		} else if (modeString[i] == '-') {
			sign = false;
		} else if (modeString[i] == 'i') {
			channel.setInviteMode(sign);
		} else if (modeString[i] == 't') {
			channel.setTopicMode(sign);
		} else if (modeString[i] == 'k' || == 'l' || == 'o') {
			if (++modeArgIndex > parameters.size() - 2) {
				client.sendMessage("NOTENOUGHPARAMS");
				continue;
			} else if (modeString[i] == 'k') {
				rply = channel.setPassword(sign, parameters[modeArgIndex]); //ERR_INVALIDKEY || already set
				if (!rply.empty())
					client.sendMessage(rply);
			} else if (modeString[i] == 'l') {
				channel.setLimit(sign ? std::atoi(parameters[++modeArgIndex]) : 0); //ERR_INVALIDMODEPARAM
			} else if (modeString[i] == 'o') {
				if (channel.isClient(parameters[++modeArgIndex]))
					continue client.sendMessage(ERR_USERNOTINCHANNEL);
				target = channel.getClients().at(parameters[modeArgIndex]);
				(sign) ? channel.addOperator(target) : channel.rmOperator(target);
		} else {
			client.sendMessage(ERR_UMODEUNKNOWNFLAG);
		}
	}
