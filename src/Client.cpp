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

void	Client::recvPackets(void) {
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
			std::cout << "Pckt recv on " << _sd << std::endl;
			std::cout << "Pckt: " << _recvBuffer << std::endl;
			_recvString.push_back(_recvBuffer);
		}
	}
}

void	Client::sendPackets(void) {
	int	rc;

	while (!_sendBuffer.empty()) {
		rc = send(_sd, _sendBuffer.c_str(), sizeof(_sendBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror(errno)); //"send() failed"
		} else if (rc < 0) {
			break;
		} else {
			std::cout << "Pckt sent on " << _sd << std::endl;
			std::cout << "Pckt: " << _sendBuffer << std::endl;
		}
	}
}

void	Client::parse(void) {
	if (_recvString.find("\r\n") != std::string::npos) {
		_recvMessage.parse(_recvString);
	}
}

void	Client::setStatus(bool status) {
	_status = status;
}

bool	Client::getStatus(void) const {
	return _status;
}
