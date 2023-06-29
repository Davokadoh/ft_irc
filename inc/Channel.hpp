#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <set>
# include "Client.hpp"

class	Channel
{
	private:
		std::set<Client*>	_client;
		Channel(const Channel &rhs);
		Channel	&operator=(const Channel &rhs);

	public:
		Channel(void);
		~Channel(void);

		void addClient(Client *client);
};

#endif
