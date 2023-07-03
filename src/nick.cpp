#include	"server.hpp"

#define INVALID_CHARS "*$%" //Need to check this list

bool	isNickValid(const std::string &nick)
{
	if (nick.find_first_of(INVALID_CHARS) == std::string::npos)
		return 0;
	return 1;
}

void    Server::nick(Client &client) {
    std::string    nickname = client.getMessage().getParameters()[0];


    if (nickname.empty())
	{
		std::cout << "Error: empty nickname" << std::endl;
        //reply("ERROR EMPTY USERNAME"); //ERR_NONICKNAMEGIVEN
    }
	else if (client.getMessage().getParameters().size() != 0)
	{
		std::cout << "Error: wrong number of paramaters" << std::endl;
	}
	else if (_clients.find(nickname) != _clients.end())
	{
		std::cout << "Error: nickname aleardy in use" << std::endl;
        //reply("COLLISION"); //ERR_NICKNAMEINUSE
    }
	else if (isNickValid(nickname))
	{
        //reply("Invalid char"); //ERR_ERRONEUSNICKNAME
    }
	else
	{
        client.setNickname(nickname);
       // reply("SUCCESS");
        //sendToAll("SUCCESS");
    }
}