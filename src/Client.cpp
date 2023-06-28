#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

Client::Client(int sd) : _sd(sd), _status(CONNECTED) {
}

Client::Client(const Client &ref) {
	*this = ref;
}

Client	&Client::operator=(const Client &rhs) {
	if (this != &rhs) {
		_sd = rhs._sd;
		_nickname = rhs._nickname;
		_username = rhs._username;
		_realname = rhs._realname;
	}

	return *this;
}

Client::~Client(void) {
	close(_sd);
}

void	Client::recvMsg(void) { //maybe rename recvPackets
	int	rc;

	while (true) {
		rc = recv(_sd, _recvBuffer, sizeof(_recvBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror(errno)); //"recv() failed"
		} else if (rc < 0) {
			break;
		} else if (rc == 0) {
			setStatus(DISCONNECTED);
			break;
		} else {
			std::cout << "Packet on " << _sd << std::endl;
			std::cout << _recvBuffer << std::endl;
			break;
		}
	}
}

void	Client::sendMsg(void) { //rename sendPackets
	int	rc;

	while (!_sendBuffer.empty()) {
		rc = send(_sd, _sendBuffer.c_str(), sizeof(_sendBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror(errno)); //"send() failed"
		} else if (rc < 0) {
			break;
		} else {
			std::cout << "Client[" << _sd << "] sends a msg" << std::endl;
		}
	}
}

void	Client::setStatus(bool status) {
	_status = status;
}

bool	Client::getStatus(void) const {
	return _status;
}
