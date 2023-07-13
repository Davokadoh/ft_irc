#include "Channel.hpp"
#include <algorithm>

Channel::Channel(void) {}

Channel::Channel(const std::string &name) : _name(name) {}

Channel::Channel(const Channel &rhs) {
	*this = rhs;
}

Channel	&Channel::operator=(const Channel &rhs) {
	if (this != &rhs) {
		this->_clients = rhs._clients;
	}
	return *this;
}

Channel::~Channel(void) {}

void	Channel::sendToAll(const std::string &msg) {
	for (std::set<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		(*it)->sendMessage(msg);
	}
}

std::string	Channel::getName(void) const {
	return _name;
}

std::string	Channel::getTopic(void) const {
	return _topic;
}

void	Channel::setTopic(const std::string &topic) {
	_topic = topic;
}

bool	Channel::getTopicMode(void) const {
	return _topicMode;
}

void	Channel::setTopicMode(const std::string &mode) {
	(void) mode;
	std::cerr << "Not implemented yet" << std::endl;
}

std::set<Client*>	Channel::getClients(void) const {
	return _clients;
}

bool	Channel::isClient(Client *client) const {
	return (_clients.find(client) == _clients.end())
	? false : true;
}

void	Channel::addClient(Client *client) {
	_clients.insert(client);
}

void	Channel::rmClient(Client *client) {
	_clients.erase(client);
}

std::set<Client*>	Channel::getOperators(void) const {
	return _operators;
}

bool	Channel::isOperator(Client &client) const {
	return (_operators.find(&client) == _operators.end())
	? false : true;
}

void	Channel::addOperator(Client &client) {
	_operators.insert(&client);
}

void	Channel::rmOperator(Client &client) {
	_operators.erase(&client);
}

/*
std::set<Client*>	Channel::getInviteds(void) const {
	return _operators;
}
*/

bool	Channel::isInvited(Client &client) const {
	return (_operators.find(&client) == _operators.end())
	? false : true;
}

void	Channel::addInvited(Client &client) {
	_operators.insert(&client);
}

void	Channel::rmInvited(Client &client) {
	_operators.erase(&client);
}

/*
void	printClient(const Client *client) {
	std::cout << client->getNickname() << std::endl;
}

void	Channel::printClientList(void) {
	std::cout << "Clients: " << std::endl;
    std::for_each(_clients.begin(), _clients.end(), printClient);
}
*/
