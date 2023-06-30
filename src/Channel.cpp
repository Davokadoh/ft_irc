#include "Channel.hpp"

// ------- COPLIEN -------

Channel::Channel(void) {}

Channel::Channel(const Channel &rhs)
{
	*this = rhs;
}

Channel	&Channel::operator=(const Channel &rhs)
{
	if (this != &rhs)
	{
		this->_clients = rhs._clients;
	}
	return (*this);
}

Channel::~Channel(void) {}

// ------- MEMBER FONCTIONS -------

void	Channel::addClient(Client *client)
{
	std::set<Client*>::iterator it = this->_clients.find(client);

	if (it == this->_clients.end())
	{
		this->_clients.insert(client);
	}
}

// <--------- just to test: greg

void	Channel::printClientList(void)
{
	std::cout << "Clients: " << std::endl;
	for (std::set<Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}
