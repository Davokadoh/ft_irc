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
	return (_clients.find(nick) != _clients.end()) ? 0 : 1;
}

# define ERR_NONICKNAMEGIVEN(arg) (arg + ":No nickname given")
void    Server::nick(Client &client) {
	if (client.getMessage().getParameters().size() == 0) {
		return client.sendMessage(ERR_NONICKNAMEGIVEN(_name));
	}
	std::string    nickname = client.getMessage().getParameters()[0];

	if (isNickInUse(nickname))
	{
		return client.sendMessage("in use");
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
