#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <sys/socket.h>
# include <sys/select.h>
# include <string>
# include <map>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/wait.h>
# include <signal.h>
# include "Channel.hpp"
# include "Macros.hpp"

class Server;

typedef void (Server::*FunPtr)(Client &client);

class Server {
	private:
		struct addrinfo		*getAddr(void);
		void				addSocket(int sd);
		void				rmSocket(int sd);
		void				addClients(void);
		void				rmClients(void);
		void				cull(void);
		void				execute(Client &client);
		void				registration(Client &client);
		int					nbrRegistered(void);
		void				addHashtag(std::string &str);
		bool				isNickInUse(const std::string &nick);

		void				nick(Client &client);
		void				user(Client &client);
		void				join(Client &client);
		void				names(Client &client);
		void				topic(Client &client);
		void				kick(Client &client);
		static std::map<std::string, FunPtr>	createMap(void);
	
		static const std::map<std::string, FunPtr>	_cmds;
		std::map<std::string, Channel*> _channels;
		std::map<std::string, Client*>	_nicknames;
		std::map<int, Client*>			_clients;
		std::string						_password;
		std::string						_port;
		std::string						_name;
		fd_set							_mainSet;
		fd_set							_recvSet;
		fd_set							_sendSet;
		bool							_status;
		int								_listenSd;
		int								_maxSd;

	public:
		Server(const std::string &port = "6667", const std::string &password = "");
		Server(const Server &ref);
		Server	&operator=(const Server &rhs);
		~Server(void);

		void	watch(void);
		void	run(void);
};

#endif
