#ifndef CLIENT_HPP
# define CLIENT_HPP

# define DISCONNECTED 1
# define CONNECTED 0

# include <string>

class Client {
	private:
		int			_sd;
		bool		_status;
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
		void	setStatus(bool status);
		bool	getStatus(void) const;
};

#endif
