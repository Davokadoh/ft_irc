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
		this->_client = rhs._client;
	}
	return (*this);
}

Channel::~Channel(void) {}

// ------- MEMBER FONCTIONS -------

void	Channel::addClient(Client *client)
{
	std::set<Client*>::iterator it = this->_client.find(client);

	if (it != this->_client.end())
	{
		this->_client.insert(client);
	}
}
