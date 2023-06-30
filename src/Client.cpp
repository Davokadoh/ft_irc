#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

Client::Client(int sd) :
	_sd(sd),
	_status(CONNECTED),
	_recvString("") {
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
		bzero(_recvBuffer, 512);
		rc = recv(_sd, _recvBuffer, sizeof(_recvBuffer), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			throw std::runtime_error(std::strerror(errno)); //"recv() failed"
		} else if (rc < 0) {
			break;
		} else if (rc == 0) {
			setStatus(DISCONNECTED);
			break;
		} else {
			std::cout << _sd << ":Pckt recv: " << _recvBuffer << std::endl;
			_recvString.append(_recvBuffer);
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
			std::cout << _sd << ":Pckt sent: " << _sendBuffer << std::endl;
		}
	}
}

void	Client::parse(void) {
	std::string::size_type pos;

	pos = _recvString.find("\r\n");
	if (pos != std::string::npos) {
		_recvMessage.clearMessage();
		_recvMessage.parse(_recvString.substr(0, pos+2));
		this->_verb = this->_recvMessage.getVerb(); // <--------- just to test: greg
		this->_parameters = this->_recvMessage.getParameters(); // <--------- just to test: greg
		std::cout << "Parsing message..." << std::endl;
		std::cout << _recvString.substr(0, pos+2) << std::endl;
		_recvString.erase(0, pos+2);
	} else if (_recvString.size() > 512) {
		throw std::runtime_error("Client sent message too long");
	}
}

void	Client::setStatus(bool status) {
	_status = status;
}

bool	Client::getStatus(void) const {
	return _status;
}


// <--------- just to test: greg
std::string	Client::getVerb(void) const
{
	return (this->_verb);
}

void	Client::setVerb(std::string str)
{
	this->_verb = str;
}

std::vector<std::string>	Client::getParameters(void) const
{
	return (this->_parameters);
}
