#include	"Server.hpp"

#define VALID_CHARS "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" //Need to check this list

bool	isNickValid(const std::string &nick) {
	return (nick.find_first_not_of(VALID_CHARS) != std::string::npos) ? 1 : 0;
}

bool	Server::isNickInUse(const std::string &nick) {
	return (_nicknames.find(nick) != _nicknames.end()) ? 1 : 0;
}

#define ERR_NONICKNAMEGIVEN(nickname) " 431 " + nickname + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickname, newNick) " 432 " + nickname + " " + newNick + " :Erroneous Nickname"
#define ERR_NICKNAMEINUSE(nickname, newNick) " 433 " + nickname + " " + newNick + " :Nickname already in use."
void    Server::nick(Client &client) {
	std::vector<std::string>	p = client.getMessage().getParameters();
    std::string					nickname = "";

	if (p.size() != 0) {
		nickname = p[0];
	}

	if (nickname.empty()) {
		client.sendMessage(this->_name + ERR_NONICKNAMEGIVEN(client.getNickname()));
  } else if (isNickValid(nickname)) {
		client.sendMessage(this->_name + ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
	}
	else if (isNickInUse(nickname)) {
		client.sendMessage(this->_name + ERR_NICKNAMEINUSE(client.getNickname(), nickname));
	} else {
		std::string	oldNick = client.getNickname();
    if (nickname != "*") {
			_nicknames.erase(client.getNickname());
		}
		_nicknames.insert(std::make_pair(nickname, &client));
		client.setNickname(nickname);
		client.sendMessage(":" + oldNick + " NICK " + client.getNickname());
		if (client.getUsername() != "" && client.getRealname() != "" && client.getIsRegistered() == false) {
			this->registration(client);
		}
	}
}
