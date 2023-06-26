#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client {
	private:
		Client(const Client &ref);
	
		int			_sd;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;

	public:
		Client(int sd = -1);
		Client	&operator=(const Client &rhs);
		~Client(void);

		void	recvMsg(void);
		void	sendMsg(void);
};

#endif
