#include "Server.hpp"
#include "fstream"

void Server::motd(Client &client)
{
	std::ifstream motd;
	std::string		line;

	motd.open("motd.txt");

	if (motd.is_open())
	{
		client.sendMessage(_name + RPL_MOTDSTART(client.getNickname()));
		while (std::getline(motd, line))
		{
			client.sendMessage(_name + RPL_MOTD(client.getNickname(), line));
		}
		client.sendMessage(_name + RPL_ENDOFMOTD(client.getNickname()));
		return;
	}
	else
	{
		client.sendMessage(this->_name + ERR_NOMOTD(client.getNickname()));
		return;
	}
}
