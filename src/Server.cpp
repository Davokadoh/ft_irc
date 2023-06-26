#include "Server.hpp"
#include <unistd.h>

Server::Server(const int port, const std::string &password) :
	_status(true), _port(port), _password(password) {
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
		if (FD_ISSET(i, _mainSet)) {
			close(i);
		}
	}
}

void	Server::listen(void) {
	_listenSd = socket(AF_INET6, SOCK_STREAM, 0);
	if (_listenSd < 0) {
		throw std::runtime_error("socket() failed");
	}
	if (setsockopt(_listenSd, SOL_SOCKET, SO_REUSEADDR, &1, sizeof(1)) < 0) {
		throw std::runtime_error("setsockopt() failed");
	}
	if (fcntl(_listenSd, F_SETFL, O_NONBLOCK) < 0) {
		throw std::runtime_error("fcntl() failed");
	}
	struct sockaddr_in addr = getAddr();
	if (bind(_listenSd, addr, sizeof(addr)) < 0) {
		throw std::runtime_error("bind() failed");
	}
	if (listen(_listenSd, 32) < 0) {
		throw std::runtime_error("listen() failed");
	}
	addSocket(_listenSd);
}

void	Server::getAddr(void) {
	struct sockaddr_in	addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr.sin6_port = htons(_port);
}

void	Server::addSocket(int sd) {
	FD_SET(sd, _mainSet);
	if (sd > _maxSd) {
		_maxSd = sd;
	}
}

void	Server::rmSocket(int sd) {
	FD_CLR(sd, _mainSet);
	if (sd == _maxSd) {
		while (!FD_ISSET(--_maxSd, _mainSet));
	}
}

void	Server::run(void) {
	while (_status) {
		cull();
		if (FD_ISSET(_listenSd, &_recvSet)) {
			addClients();
		}
		for (int i = 0; i < _maxSd; ++i) {
			if (FD_ISSET(i, readSet)) {
				clients[i].recvMsg();
			}
			if (FD_ISSET(i, sendSet)) {
				clients[i].sendMsg();
			}
		}
	}
}

void	Server::cull(void) {
	FD_COPY(_mainSet, _recvSet);
	FD_COPY(_mainSet, _sendSet);
	_selected = select(_clients.rbegin()->first + 1, &_recvSet, &_sendSet, NULL, NULL);
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
		clients.insert(sd, Client(sd));
	} while (sd >= 0);
	FD_CLR(_listenSd, &_recvSet);
}
