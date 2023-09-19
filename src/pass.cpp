#include "Server.hpp"

void Server::pass(Client &client)
{
	if (client.getMessage().getParameters().size() < 1)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
		return;
	}
	if (client.getIsPassOK() == true)
	{
		client.sendMessage(this->_name + ERR_ALREADYREGISTERED(client.getNickname()));
		return;
	}
	std::string pass = client.getMessage().getParameters()[0];
	if (this->_password != pass)
	{
		client.sendMessage(this->_name + ERR_PASSWDMISMATCH(client.getNickname()));
		return;
	}
	else
	{
		client.setIsPassOK(true);
	}
}
