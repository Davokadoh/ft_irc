#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include "Macros.hpp"
#include <iostream>
#include <set>

enum Mode
{
	i,
	k,
	l,
	t
};

class Channel
{
private:
	Channel(void);
	Channel(const Channel &rhs);
	Channel &operator=(const Channel &rhs);

	std::set<Client *>			 _clients;
	std::set<Client *>			 _operators;
	std::set<Client *>			 _inviteList;
	bool										 _modes[4];
	static const std::string _modesStr[4];
	std::string							 _name;
	std::string							 _serverName;
	std::string							 _topic;
	std::string							 _password;
	unsigned int						 _limit;

public:
	Channel(const std::string &name, const std::string &serverName);
	~Channel(void);

	void				sendToAll(const std::string &msg, Client *exception);
	std::string getName(void) const;
	std::string getModes(void) const;
	bool				getMode(Mode mode) const;
	void				setMode(Client &client, Mode mode, bool sign);

	unsigned int getLimit(void) const;
	std::string	 getTopic(void) const;
	void				 setTopic(const std::string &topic);

	void							 setPassword(Client &client, const bool mode, const std::string &password);
	const std::string &getPassword(void) const;
	void							 setLimit(Client &client, const bool mode, const std::string &limitStr);
	void							 setOperatorMode(Client &client, const bool mode, const std::string &nick, Client *target);

	bool							 isEmpty(void) const;
	std::set<Client *> getClients(void) const;
	bool							 isClient(Client *client) const;
	void							 addClient(Client *client);
	void							 rmClient(Client *client);
	// std::set<Client *> getOperators(void) const;
	bool isOperator(Client &client) const;
	void addOperator(Client &client);
	void rmOperator(Client &client);
	// std::set<Client *> getInviteList(void) const;
	bool isInvited(Client &client) const;
	void addInvited(Client &client);
	void rmInvited(Client &client);
	// void setInviteList(Client *client);
};

#endif
