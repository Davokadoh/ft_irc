#include	"Server.hpp"
#include 	<netdb.h>

#define ERR_NEEDMOREPARAMS(nickname) " 461 " + nickname + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(nickname) " 462 " + nickname + " :You may not reregister"
#define RPL_WELCOME(nickname, servername) " 001 " + nickname + " :Welcome to the " + servername + " Network " + nickname
#define RPL_YOURHOST(nickname, servername) " 002 " + nickname + " :Your host is " + servername
#define RPL_CREATED(nickname) " 003 " + nickname + " :This server was created today"
#define RPL_MYINFO(nickname, servername) " 004 " + nickname + " " + servername
#define RPL_ISUPPORT(nickname) " 005 " + nickname + " JE SAIS PAS"

void	Server::user(Client &client)
{
	if (client.getMessage().getParameters().size() < 4)
	{
		client.sendMessage(this->_name + ERR_NEEDMOREPARAMS(client.getNickname()));
	}
	else if (client.getIsRegistered() == true)
	{
		client.sendMessage(this->_name + ERR_ALREADYREGISTERED(client.getNickname()));
	}
	else
	{
		client.setUsername(client.getMessage().getParameters()[0]);
		client.setRealname(client.getMessage().getParameters()[3]);
		if (client.getNickname() != "*")
		{
			client.setIsRegistered(true);
			client.sendMessage(this->_name + RPL_WELCOME(client.getNickname(), this->_name));
			client.sendMessage(this->_name + RPL_YOURHOST(client.getNickname(), this->_name));
			client.sendMessage(this->_name + RPL_CREATED(client.getNickname()));
			client.sendMessage(this->_name + RPL_MYINFO(client.getNickname(), this->_name));
			client.sendMessage(this->_name + RPL_ISUPPORT(client.getNickname()));
		}
	}
}
