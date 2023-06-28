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

class Server {
	private:
		struct addrinfo	*getAddr(void);
		void			addSocket(int sd);
		void			rmSocket(int sd);
		void			cull(void);
		void			addClients(void);
		void			rmClients(void);
	
		std::map<int, Client*>	_clients;
		fd_set					_mainSet;
		fd_set					_recvSet;
		fd_set					_sendSet;
		bool					_status;
		int						_listenSd;
		int						_maxSd;
		int						_port;
		std::string				_password;

	public:
		Server(const int port = -1, const std::string &password = "");
		Server(const Server &ref);
		Server	&operator=(const Server &rhs);
		~Server(void);

		void	watch(void);
		void	run(void);
};

#endif