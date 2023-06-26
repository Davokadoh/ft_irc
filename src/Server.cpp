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
	close(_listenSd);

	for(int i = 0; i < _mainSet.fd_count; ++i)
		close(_mainSet.fd_array[i]);
	}
}

void	Server::listen(void) {
	_listenSd = socket(AF_INET6, SOCK_STREAM, 0);
	if (setsockopt(_port, SOL_SOCKET, SO_REUSEADDR, (char *)&true, sizeof(true)) < 0) {
		throw std::runtime_error("socket() failed");
	}
	if (ioctl(_listenSd, FIONBIO, (char *)&on) < 0) {
		throw std::runtime_error("ioctl() failed");
	}
	getAddrStruct();
	if (bind(_listenSd, addr, sizeof(addr)) < 0) {
		throw std::runtime_error("bind() failed");
	}
	if (listen(_listenSd, 32) < 0) {
		throw std::runtime_error("listen() failed");
	}
}

void	Server::getAddrStruct(void) {
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr.sin6_port = htons(_port);
}

void	Server::run(void) {
	while (_status) {
		cullSelected();
		if (FD_ISSET(_listenSd, &_recvSet)) {
			addClients();
		}
		for (socket : _recvSet) {
			clients[socket].recvMsg();
		}
		for (socket : _sendSet) {
			clients[socket].sendMsg();
		}
	}
}

void	Server::cullSelected(void) {
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
