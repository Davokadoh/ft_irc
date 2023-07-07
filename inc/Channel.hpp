#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <set>
# include "Client.hpp"

class	Channel
{
	private:
		Channel(const Channel &rhs);
		Channel	&operator=(const Channel &rhs);

		std::set<Client*>	_clients;
		std::set<Client*>	_operators;
		bool				_inviteMode;
		bool				_topicMode;
		std::string			_topic;
		std::string			_password;
		unsigned int		_limit;

	public:
		Channel(void);
		~Channel(void);

		void				addClient(Client *client);
		std::set<Client*>	getClients(void) const;
		void				printClientList(void);
};

#endif

i: Invite-only channel
t: Restricts TOPIC command to channel operators
k: Set/remove the channel key (password)
o: Give/take channel operator privilege
l: Set/remove the user limit to channel
