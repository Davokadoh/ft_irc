#ifndef CLIENT_HPP
# define CLIENT_HPP

# define DISCONNECTED 1
# define CONNECTED 0

# include <string>
# include "Message.hpp"

class Client {
	private:
		int			_sd;
		bool		_status;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_sendBuffer;
		std::string	_recvString;
		char		_recvBuffer[512];
		Message		_recvMessage;

	public:
		Client(int sd = -1);
		Client(const Client &ref);
		Client	&operator=(const Client &rhs);
		~Client(void);

		void	recvPackets(void);
		void	sendPackets(void);
		void	setStatus(bool status);
		bool	getStatus(void) const;
		void	parse(void);

		Message	&getRecvMessage(void); // <--------- just to test: greg
};

#endif
