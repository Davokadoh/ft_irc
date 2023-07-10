#include "Server.hpp"
#include <sys/errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ctime>

std::map<std::string, FunPtr>	Server::createMap(void) {
	std::map<std::string, FunPtr>	cmds;
	cmds["NICK"] = &Server::nick;
	cmds["USER"] = &Server::user;
	cmds["JOIN"] = &Server::join;
	cmds["NAMES"] = &Server::names;
	cmds["TOPIC"] = &Server::topic;
	cmds["KICK"] = &Server::kick;
	return cmds;
}

const std::map<std::string, FunPtr> Server::_cmds = Server::createMap();

Server::Server(const std::string &port, const std::string &password) : _password(password), _port(port), _name(":ft_irc.42.ch"), _status(true), _maxSd(1) {
	FD_ZERO(&_mainSet);
	FD_ZERO(&_recvSet);
	FD_ZERO(&_sendSet);
}

Server::Server(const Server &ref) {
	*this = ref;
}

Server	&Server::operator=(const Server &rhs) {
	if (this != &rhs) {
		_listenSd = rhs._listenSd;
		_clients = rhs._clients;
		_mainSet = rhs._mainSet;
		_recvSet = rhs._recvSet;
		_sendSet = rhs._sendSet;
	}

	return *this;
}

Server::~Server(void) {
	for(int i = 0; i < _maxSd; ++i) {
		if (FD_ISSET(i, &_mainSet)) {
			rmSocket(i);
		}
	}
}

void	Server::watch(void) {
	int	yes=1;
	struct addrinfo	*addr = getAddr();

	_listenSd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (_listenSd < 0) {
		throw std::runtime_error("socket() failed");
	}
	if (setsockopt(_listenSd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
		throw std::runtime_error("setsockopt() failed");
	}
	if (fcntl(_listenSd, F_SETFL, O_NONBLOCK) < 0) {
		throw std::runtime_error("fcntl() failed");
	}
	if (bind(_listenSd, addr->ai_addr, addr->ai_addrlen) < 0) {
		throw std::runtime_error("bind() failed");
	}
	if (listen(_listenSd, 32) < 0) {
		throw std::runtime_error("listen() failed");
	}
	freeaddrinfo(addr);
	addSocket(_listenSd);
}

struct addrinfo	*Server::getAddr(void) {
	struct addrinfo	hints, *servinfo;

	memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _port.c_str(), &hints, &servinfo)) {
		//what about gai_strerror() ?
		throw std::runtime_error("getaddrinfo() failed");
	}
	return servinfo;
}

void	Server::addSocket(int sd) {
	FD_SET(sd, &_mainSet);
	if (sd > _maxSd) {
		_maxSd = sd;
	}
}

void	Server::rmSocket(int sd) {
	FD_CLR(sd, &_mainSet);
	close(sd);
	if (sd == _maxSd) {
		while (!FD_ISSET(--_maxSd, &_mainSet));
	}
}

void	Server::run(void) {
	while (_status) {
		cull();
		if (FD_ISSET(_listenSd, &_recvSet)) {
			addClients();
		}
		for (int i = 0; i <= _maxSd; ++i) {
			if (FD_ISSET(i, &_recvSet)) {
				_clients[i]->recvPackets();
			}
		}
		for (int i = 0; i <= _maxSd; ++i) {
			if (FD_ISSET(i, &_sendSet)) {
				_clients[i]->sendPackets();
			}
		}
		for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
			it->second->parse();
			execute(*(it->second));
		}
		rmClients();
	}
}

void	Server::execute(Client &client) {
	std::string	verb = client.getMessage().getVerb();

	client.setSource(":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getIp());
	if (verb.empty()) {
		return;
	} else if (_cmds.find(verb) != _cmds.end()) {
		(this->*_cmds.at(verb))(client);
	} else {
		client.sendMessage(this->_name + ERR_UNKNOWNCOMMAND(client.getNickname()));
	}
}

void	Server::cull(void) {
	int	_selected;
	FD_COPY(&_mainSet, &_recvSet);
	FD_COPY(&_mainSet, &_sendSet);
	_selected = select(_maxSd + 1, &_recvSet, &_sendSet, NULL, NULL);
	if (_selected == 0) {
		throw std::runtime_error("select() timed out");
	} else if (_selected < 0) {
		throw std::runtime_error("select() failed");
	}
}

void	Server::addClients(void) {
	int	sd;
	socklen_t	len = sizeof(struct sockaddr);
    struct sockaddr_in addr;

	do {
		sd = accept(_listenSd, (struct sockaddr *) &addr, &len);
		if (sd < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error("accept() failed");
		} else if (sd < 0) {
			break;
		}
		addSocket(sd);
		_clients.insert(std::make_pair(
			sd, new Client(sd, inet_ntoa(addr.sin_addr))));
	} while (sd >= 0);
	FD_CLR(_listenSd, &_recvSet);
}

void	Server::rmClients(void) {
	for (std::map<int, Client*>::iterator it = _clients.begin(), last = _clients.end(); it != last; ) {
		if (it->second->getStatus()) {
			rmSocket(it->first);
			_nicknames.erase(it->second->getNickname());
			it = _clients.erase(it);
		} else {
			++it;
		}
	}
}

std::string	intToString(int toStr)
{
	std::stringstream ss;
	ss << toStr;
	std::string result = ss.str();
	return (result);
}

std::string	getDateCreation(void)
{
	std::time_t now = std::time(NULL);
	struct std::tm* timeinfo = std::localtime(&now);

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	std::string result = buffer;
	return (result);
}

int	Server::nbrRegistered(void)
{
	int	clientRegist = 0;

	for (std::map<int, Client*>::iterator	it = this->_clients.begin(); it !=this->_clients.end(); it++)
	{
		if (it->second->getIsRegistered() == true)
		{
			clientRegist++;
		}
	}
	return (clientRegist);
}

void	Server::registration(Client &client)
{
	client.setIsRegistered(true);
	
	std::string nbrClients = intToString(this->nbrRegistered());
	std::string nbrChannels = intToString(this->_channels.size());

	client.sendMessage(this->_name + RPL_WELCOME(client.getNickname()));
	client.sendMessage(this->_name + RPL_YOURHOST(client.getNickname()));
	client.sendMessage(this->_name + RPL_CREATED(client.getNickname(), getDateCreation()));
	client.sendMessage(this->_name + RPL_MYINFO(client.getNickname(), this->_name));
	//client.sendMessage(this->_name + RPL_ISUPPORT(client.getNickname()));
	client.sendMessage(this->_name + RPL_LUSERCLIENT(client.getNickname(), nbrClients));
	client.sendMessage(this->_name + RPL_LUSEROP(client.getNickname()));
	client.sendMessage(this->_name + RPL_LUSERCHANNELS(client.getNickname(), nbrChannels));
	client.sendMessage(this->_name + RPL_LUSERME(client.getNickname(), nbrClients));
	client.sendMessage(this->_name + ERR_NOMOTD(client.getNickname()));
}

void	Server::addHashtag(std::string &str) {
	if (str[0] != '#') {
		str.insert(0, "#");
	}
}
