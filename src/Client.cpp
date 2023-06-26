#include "Client.hpp"

Client::Client(int sd) : _sd(sd) {
}

Client::Client(const Client &ref) {
	*this = ref;
}

Client	&Client::operator=(const Client &rhs) {
	if (*this != rhs) {
		_sd = rhs._sd;
		_nickname = rhs._nickname;
		_username = rhs._username;
		_realname = rhs._realname;
	}

	return *this;
}

Client::~Client(void) {
}

Client::recvMsg(void) {
	while (true) {
		rc = recv(_sd, recvBuffer, sizeof(recvBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror()); //"recv() failed"
		} else if (rc < 0) {
			break;
		} else {
			std::cout << "Client[" << _sd << "] recvd a msg" << std::endl;
			std::cout << recvBuffer << std::endl;
		}
	}
}

Client::sendMsg(void) {
	while (sendBuffer) {
		rc = send(_sd, sendBuffer, sizeof(sendBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror()); //"send failed"
		} else if (rc < 0) {
			break;
		} else {
			std::cout << "Client[" << _sd << "] sends a msg" << std::endl;
		}
	}
}
