#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

Client::Client(int sd) :
	_sd(sd),
	_status(CONNECTED),
	_nickname("*"),
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
	while (true) {
		bzero(_recvBuff, 512);
		int rc = recv(_sd, _recvBuff, sizeof(_recvBuff), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			//"recv() failed"
			throw std::runtime_error(std::strerror(errno));
		} else if (rc < 0) {
			break;
		} else if (rc == 0) {
			setStatus(DISCONNECTED);
			break;
		} else {
			std::cout << _sd << ":Pckt recv: " << _recvBuff << std::endl;
			_recvString.append(_recvBuff);
		}
	}
}

void	Client::sendPackets(void) {
	while (!_sendBuff.empty()) {
		int rc = send(_sd, _sendBuff.c_str(), sizeof(_sendBuff), 0);
		if (rc < 0 && errno != EWOULDBLOCK) {
			//"send() failed"
			throw std::runtime_error(std::strerror(errno));
		} else if (rc < 0) {
			break;
		} else if (rc == 0) {
			setStatus(DISCONNECTED);
			break;
		} else {
			_sendBuff.erase(_sendBuff.begin(), _sendBuff.begin() + rc);
		}
	}
}

void	Client::sendMessage(const std::string &msg) {
	_sendBuff.append(this->getMessage().getHostname() + this->getMessage().getNick() + msg + "\r\n");
}

void	Client::parse(void) {
	std::string::size_type pos = _recvString.find("\r\n");
	if (pos != std::string::npos) {
		_recvMessage.clearMessage();
		_recvMessage.parse(_recvString.substr(0, pos));
		_recvString.erase(0, pos + 2);
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

Message	&Client::getMessage(void) {
	return _recvMessage;
}

// ------- GETTERS AND SETTERS -------

std::string	Client::getNickname(void) const
{
	return (this->_nickname);
}

void	Client::setNickname(std::string newNick)
{
	this->_nickname = newNick;
}
