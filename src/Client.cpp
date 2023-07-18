#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <cstring>

#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(int sd, const std::string &ip) :
	_sd(sd),
	_status(CONNECTED),
	_isRegistered(false),
	_ip(ip),
	_nickname("*"),
	_username(""),
	_source(""),
	_realname(""),
	_recvString(""){
		std::cout << "ip: " << _ip << std::endl;
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
		if (rc < 0 && errno == EWOULDBLOCK) {
			break;
		} else if (rc <= 0) {
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
		int rc = send(_sd, _sendBuff.c_str(), _sendBuff.length(), 0);
		if (rc < 0 && errno == EWOULDBLOCK) {
			break;
		} else if (rc <= 0) {
			setStatus(DISCONNECTED);
			break;
		} else {
			_sendBuff.erase(_sendBuff.begin(), _sendBuff.begin() + rc);
		}
	}
}

void	Client::sendMessage(const std::string &msg) {
	_sendBuff.append(msg + "\r\n");
}

void	Client::parse(void) {
	std::string::size_type pos = _recvString.find("\r\n");
	_recvMessage.clear();
	if (pos != std::string::npos) {
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

Message	Client::getMessage(void) const {
	return _recvMessage;
}

// ------- GETTERS AND SETTERS -------

std::string	Client::getNickname(void) const
{
	return (this->_nickname);
}

std::string	Client::getUsername(void) const
{
	return (this->_username);
}

std::string	Client::getRealname(void) const
{
	return (this->_realname);
}

std::string	Client::getSource(void) const
{
	return (this->_source);
}

std::string	Client::getIp(void) const
{
	return (this->_ip);
}

bool	Client::getIsRegistered(void) const
{
	return (this->_isRegistered);
}

void	Client::setNickname(std::string newNick)
{
	this->_nickname = newNick;
}

void	Client::setUsername(std::string username)
{
	this->_username = username;
}

void	Client::setRealname(std::string realname)
{
	this->_realname = realname;
}

void	Client::setSource(std::string source)
{
	this->_source = source;
}

void	Client::setIsRegistered(bool status)
{
	this->_isRegistered = status;
}

void	Client::resetMessage(void) {
	_recvMessage.clear();
}

void	Client::setMessage(std::string part, std::string channel)
{
	this->_recvMessage.setVerb(part);
	
	this->_recvMessage.splitParameters(channel);
}
