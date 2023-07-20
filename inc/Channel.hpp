#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include "Macros.hpp"
#include <iostream>
#include <set>

class Channel
{
private:
  Channel(void);
  Channel(const Channel &rhs);
  Channel &operator=(const Channel &rhs);

  std::set<Client *> _clients;
  std::set<Client *> _operators;
  std::set<Client *> _inviteList;
  bool               _inviteMode;
  bool               _topicMode;
  std::string        _topic;
  std::string        _password;
  std::string        _name;
  std::string        _serverName;
  unsigned int       _limit;

public:
  Channel(const std::string &name, const std::string &serverName);
  ~Channel(void);

  void        sendToAll(const std::string &msg);
  std::string getName(void) const;
  std::string getTopic(void) const;
  void        setTopic(const std::string &topic);
  bool        getTopicMode(void) const;
  void        setTopicMode(Client &client, const bool mode);
  bool        getInviteMode(void) const;
  void        setInviteMode(Client &client, const bool mode);
  void        setPassword(Client &client, const bool mode, const std::string &password);
  void        setLimit(Client &client, const bool mode, const std::string &limitStr);

  std::set<Client *> getClients(void) const;
  bool               isClient(Client *client) const;
  void               addClient(Client *client);
  void               rmClient(Client *client);
  // std::set<Client *> getOperator(void) const;
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
