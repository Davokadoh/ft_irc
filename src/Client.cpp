#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>

Client::Client(int sd) : _sd(sd) {
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
			//setStatus(bye);
			std::cerr << "CLOSED" << std::endl;
			exit(1);
		} else {
			std::cout << "Client[" << _sd << "] recvd a msg" << std::endl;
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
