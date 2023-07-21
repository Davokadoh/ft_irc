#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include <map>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>

#include "Channel.hpp"
#include "Macros.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

class Server;

typedef void (Server::*FunPtr)(Client &client);

class Server
{
private:
  struct addrinfo                           *getAddr(void);
  void                                       addSocket(int sd);
  void                                       rmSocket(int sd);
  void                                       addClients(void);
  void                                       rmClients(void);
  void                                       cull(void);
  void                                       execute(Client &client);
  void                                       registration(Client &client);
  void                                       partChannels(Client &client);
  int                                        nbrRegistered(void);
  bool                                       isNickInUse(const std::string &nick);
  std::string                                getChannelWith(Client *client);
  void                                       nick(Client &client);
  void                                       user(Client &client);
  void                                       join(Client &client);
  void                                       names(Client &client);
  void                                       topic(Client &client);
  void                                       kick(Client &client);
  void                                       mode(Client &client);
  void                                       part(Client &client);
  void                                       ping(Client &client);
  void                                       cap(Client &client);
  void                                       privmsg(Client &client);
  void                                       notice(Client &client);
  void                                       invite(Client &client);
  void                                       motd(Client &client);
  void                                       pass(Client &client);
  void                                       who(Client &client);
  static std::map<std::string, FunPtr>       createMap(void);
  static const std::map<std::string, FunPtr> _cmds;
  std::map<std::string, Channel *>           _channels;
  std::map<std::string, Client *>            _nicknames;
  std::map<int, Client *>                    _clients;
  std::string                                _password;
  std::string                                _port;
  std::string                                _name;
  fd_set                                     _mainSet;
  fd_set                                     _recvSet;
  fd_set                                     _sendSet;
  bool                                       _status;
  int                                        _listenSd;
  int                                        _maxSd;

public:
  Server(const std::string &port, const std::string &password);
  Server(const Server &ref);
  Server &operator=(const Server &rhs);
  ~Server(void);

  void watch(void);
  void run(void);
};

std::string intToString(int toStr);

#endif
