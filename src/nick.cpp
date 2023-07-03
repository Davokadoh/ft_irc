#include	"Server.hpp"

#define VALID_CHARS "\\[]{}|abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" //Need to check this list

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

void    Server::nick(Client &client) {
	if (client.getMessage().getParameters().size() != 1)
	{
		std::cout << "Error: wrong number of paramaters" << std::endl;
		return;
	}
    std::string    nickname = client.getMessage().getParameters()[0];

    if (nickname.empty())
	{
		std::cout << "Error: empty nickname" << std::endl;
		return;
        //reply("ERROR EMPTY USERNAME"); //ERR_NONICKNAMEGIVEN
    }
	else if (isNickInUse(nickname))
	{
		std::cout << "Error: nickname aleardy in use" << std::endl;
		return;
        //reply("COLLISION"); //ERR_NICKNAMEINUSE
    }
	else if (!isNickValid(nickname))
	{
		std::cout << "Error: unvalid character in nickname" << std::endl;
		return;
        //reply("Invalid char"); //ERR_ERRONEUSNICKNAME
    }
	else
	{
        client.setNickname(nickname);
       // reply("SUCCESS");
        //sendToAll("SUCCESS");
    }
	std::cout << "client nickname: " << client.getNickname() << std::endl;
}
