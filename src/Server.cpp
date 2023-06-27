#include "Server.hpp"
#include <sys/errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

Server::Server(const int port, const std::string &password) :
	_status(true), _maxSd(1), _port(port), _password(password) {
	(void) _port;
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
			close(i);
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

#define PORT "6667"

struct addrinfo	*Server::getAddr(void) {
	struct addrinfo	hints, *servinfo;

	memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, PORT, &hints, &servinfo) != 0) {
		throw std::runtime_error("getaddrinfo() failed"); //what about gai_strerror() ?
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
				std::cout << "RECEIVING" << std::endl;
				_clients[i]->recvMsg();
			}
		}
		for (int i = 0; i <= _maxSd; ++i) {
			if (FD_ISSET(i, &_sendSet)) {
				_clients[i]->sendMsg();
			}
		}
		for (int i = 0; i <= _maxSd; ++i) {
			//_clients[i].receivedMsg.parse();
		}
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

	do {
		sd = accept(_listenSd, NULL, NULL);
		if (sd < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error("accept() failed");
		} else if (sd < 0) {
			break;
		}
		std::cout << "Inserting client" << std::endl;
		addSocket(sd);
		_clients.insert(std::make_pair(sd, new Client(sd)));
	} while (sd >= 0);
	FD_CLR(_listenSd, &_recvSet);
}
