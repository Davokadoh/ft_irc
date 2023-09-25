#include "Server.hpp"

void Server::pass(Client &client)
{
	if (client.getMessage().getParameters().size() < 1)
		return client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));

	if (client.getIsPassOK() == true)
		return client.sendMessage(this->_name + ERR_ALREADYREGISTERED(client.getNickname()));
	std::string pass = client.getMessage().getParameters()[0];
	if (this->_password != pass)
		return client.sendMessage(this->_name + ERR_PASSWDMISMATCH(client.getNickname()));
	else
		client.setIsPassOK(true);
}
