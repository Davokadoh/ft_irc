#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client {
	private:
		int			_sd;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_sendBuffer;
		char		_recvBuffer[512];

	public:
		Client(int sd = -1);
		Client(const Client &ref);
	
		Client	&operator=(const Client &rhs);
		~Client(void);

		void	recvMsg(void);
		void	sendMsg(void);
};

#endif
