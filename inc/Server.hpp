#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <sys/select.h>
# include <string>
# include <map>

class Server {
	private:
		Server(const Server &ref);

		void	getAddrStruct(void);
		void	cullSelected(void);
		void	addClients(void);
	
		std::map<int, Client>	_clients;
		fd_set					_mainSet;
		fd_set					_recvSet;
		fd_set					_sendSet;
		bool					_status;
		int						_listenSd;
		int						_port;
		std::string				_password;

	public:
		Server(const int port = -1, const std::string &password = "");
		Server	&operator=(const Server &rhs);
		~Server(void);

		void	listen(void);
		void	run(void);
};

#endif
