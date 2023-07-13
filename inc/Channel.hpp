#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <set>
# include "Client.hpp"
# include "Macros.hpp"

class	Channel
{
	private:
		Channel(void);
		Channel(const Channel &rhs);
		Channel	&operator=(const Channel &rhs);

		std::set<Client*>	_clients;
		std::set<Client*>	_operators;
		bool				_inviteMode;
		bool				_topicMode;
		std::string			_topic;
		std::string			_password;
		std::string			_name;
		//unsigned int		_limit;

	public:
		Channel(const std::string &name);
		~Channel(void);

		void				sendToAll(const std::string &msg);
		std::string			getName(void) const;
		std::string			getTopic(void) const;
		void				setTopic(const std::string &topic);
		bool				getTopicMode(void) const;
		void				setTopicMode(const std::string &mode);
		std::set<Client*>	getClients(void) const; //to rm
		bool				isClient(Client *client) const;
		void				addClient(Client *client);
		void				rmClient(Client *client);
		std::set<Client*>	getOperators(void) const; //to rm
		bool				isOperator(Client &client) const;
		void				addOperator(Client &client);
		void				rmOperator(Client &client);
		//std::set<Client*>	getInviteds(void) const; //to rm
		bool				isInvited(Client &client) const;
		void				addInvited(Client &client);
		void				rmInvited(Client &client);
		//void				printClientList(void);
};

#endif

/*
i: Invite-only channel
t: Restricts TOPIC command to channel operators
k: Set/remove the channel key (password)
o: Give/take channel operator privilege
l: Set/remove the user limit to channel
*/
