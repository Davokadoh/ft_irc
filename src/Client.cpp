#include "Client.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>

Client::Client(int sd, const std::string &ip)
  : _sd(sd), _rdyToSend(false), _status(CONNECTED), _isRegistered(false), _isPassOK(false), _ip(ip), _nickname("*"), _username(""), _source(""), _realname(""), _recvString("")
{
  std::cout << "ip: " << _ip << std::endl;
}

Client::Client(const Client &ref)
{
  *this = ref;
}

Client &Client::operator=(const Client &rhs)
{
  if (this != &rhs)
  {
    _sd = rhs._sd;
    _nickname = rhs._nickname;
    _username = rhs._username;
    _realname = rhs._realname;
  }
  return *this;
}

Client::~Client(void)
{
  close(_sd);
}

void Client::recvPackets(void)
{
  if (getStatus() == DISCONNECTED)
    return;
  std::cout << "Receiving packet" << std::endl;
  bzero(_recvBuff, 512);
  int rc = recv(_sd, _recvBuff, sizeof(_recvBuff), 0);
  if (rc <= 0)
  {
    setStatus(DISCONNECTED);
  }
  else
  {
    _recvString.append(_recvBuff);
  }
}

void Client::sendPackets(void)
{
  if (getStatus() == DISCONNECTED)
    return;
  std::cout << "Sending packet" << std::endl;
  if (_sendBuff.empty())
    return;
  int rc = send(_sd, _sendBuff.c_str(), _sendBuff.length(), 0);
  if (rc < 0)
  {
    setStatus(DISCONNECTED);
    setRdyToSend(false);
  }
  else
  {
    _sendBuff.erase(_sendBuff.begin(), _sendBuff.begin() + rc);
  }
  if (_sendBuff.empty())
  {
    setRdyToSend(false);
  }
}

void Client::sendMessage(const std::string &msg)
{
  _sendBuff.append(msg + "\r\n");
  setRdyToSend(true);
}

void Client::parse(void)
{
  std::string::size_type pos = _recvString.find("\r\n");
  _recvMessage.clear();
  if (pos != std::string::npos)
  {
    _recvMessage.parse(_recvString.substr(0, pos));
    _recvString.erase(0, pos + 2);
  }
  else if (_recvString.size() > 512)
  {
    throw std::runtime_error("Client sent message too long");
  }
}

void Client::setStatus(bool status)
{
  _status = status;
}

bool Client::getStatus(void) const
{
  return _status;
}

Message Client::getMessage(void) const
{
  return _recvMessage;
}

// ------- GETTERS AND SETTERS -------

std::string Client::getNickname(void) const
{
  return (this->_nickname);
}

std::string Client::getUsername(void) const
{
  return (this->_username);
}

std::string Client::getRealname(void) const
{
  return (this->_realname);
}

std::string Client::getSource(void) const
{
  return (this->_source);
}

std::string Client::getIp(void) const
{
  return (this->_ip);
}

std::string Client::getSendBuff(void) const
{
  return (this->_sendBuff);
}

bool Client::getIsRegistered(void) const
{
  return (this->_isRegistered);
}

bool Client::getIsPassOK(void) const
{
  return (this->_isPassOK);
}

bool Client::getRdyToSend(void) const
{
  return (this->_rdyToSend);
}

void Client::setNickname(std::string newNick)
{
  this->_nickname = newNick;
}

void Client::setUsername(std::string username)
{
  this->_username = username;
}

void Client::setRealname(std::string realname)
{
  this->_realname = realname;
}

void Client::setSource(std::string source)
{
  this->_source = source;
}

void Client::setIsRegistered(bool status)
{
  this->_isRegistered = status;
}

void Client::setIsPassOK(bool status)
{
  this->_isPassOK = status;
}

void Client::setRdyToSend(bool status)
{
  this->_rdyToSend = status;
}

void Client::resetMessage(void)
{
  _recvMessage.clear();
}

void Client::setMessage(std::string part, std::string channel)
{
  this->_recvMessage.setVerb(part);
  this->_recvMessage.splitParameters(channel);
}
