#include	"Server.hpp"

#define VALID_CHARS "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" //Need to check this list

bool	isNickValid(const std::string &nick)
{
	if (nick.find_first_not_of(VALID_CHARS) != std::string::npos)
		return 0;
	return 1;
}

bool	Server::isNickInUse(const std::string &nick)
{
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if ((it->second->getNickname() == nick))
			return 1;
	return 0;
}

# define ERR_NONICKNAMEGIVEN(nickname) " 431 " + nickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname, newNick) " 432 " + nickname + " " + newNick + " :Erroneous Nickname"
# define ERR_NICKNAMEINUSE(nickname, newNick) " 433 " + nickname + " " + newNick + " :Nickname already in use."

void    Server::nick(Client &client) {

    std::string    nickname = client.getMessage().getParameters()[0];

	if (nickname.empty())
	{
		client.sendMessage(this->_name + ERR_NONICKNAMEGIVEN(client.getNickname()));
	}
	else if (!isNickValid(nickname))
	{
		std::cout << "not valid ..........." << std::endl;
		client.sendMessage(this->_name + ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
	}
	else if (isNickInUse(nickname))
	{
		std::cout << "used ---------" << std::endl;
		client.sendMessage(this->_name + ERR_NICKNAMEINUSE(client.getNickname(), nickname));
	}
	else
	{
		std::string	oldNick = client.getNickname();
		client.setNickname(nickname);
		client.sendMessage(":" + oldNick + " NICK " + client.getNickname());
		if (client.getUsername() != "" && client.getRealname() != "" && client.getIsRegistered() == false)
		{
			this->registration(client);
		}
	}
	std::cout << "client nickname: " << client.getNickname() << std::endl;
}
