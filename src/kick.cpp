void	Server::kick(Client &client) {
	Message	message = client.getMessage();
	std::vector<std::string>	parameters = message.getParameters();
	std::string	channel = parameters[0];
	std::string	target = parameters[1];
	std::map<>	operators = channel.getOperators();

	if (channel.empty()) {
		rply(NOSUCHCHANNEL);
		return;
	} else if (clients.find(client) == clients.end()) {
		rply(NOTONCHANNEL);
		return;
	} else if (operators.find(client) == operators.end()) {
		rply(ERR_CHANOPRIVSNEEDED);
		return;
	} else if (clients.find(target) == clients.end()) {
		rply(ERR_USERNOTINCHANNEL);
		return;
	} else {
		channel.rmClient(target);
	}
}
