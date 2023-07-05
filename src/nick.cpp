#include	"Server.hpp"

#define VALID_CHARS "\\[]{}|abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" //Need to check this list

bool	isNickValid(const std::string &nick) {
	return (nick.find_first_not_of(VALID_CHARS) != std::string::npos) ? 1 : 0;
}

bool	Server::isNickInUse(const std::string &nick) {
	return (_nicknames.find(nick) != _nicknames.end()) ? 1 : 0;
}

#define ERR_NONICKNAMEGIVEN(arg) (arg + ":No nickname given")
void    Server::nick(Client &client) {
	std::vector<std::string>	p = client.getMessage().getParameters();

	if (p.size() == 0) {
		return client.sendMessage(ERR_NONICKNAMEGIVEN(_name));
	} else if (isNickInUse(p[0])) {
		return client.sendMessage("in use");
		std::cout << "Nickname aleardy in use" << std::endl;
		return;
	} else if (isNickValid(p[0])) {
		std::cout << "Invalid character in nickname" << std::endl;
		return;
	} else {
		if (p[0] != "*") {
			_nicknames.erase(client.getNickname());
		}
		_nicknames.insert(std::make_pair(p[0], &client));
		client.setNickname(p[0]);
	}
	/*
	for (auto it=_nicknames.begin();it!=_nicknames.end();++it) {
		std::cout << it->first << std::endl;
	}
	*/
}
