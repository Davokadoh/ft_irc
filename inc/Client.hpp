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

		std::string _verb; // <--------- just to test: greg
		std::vector<std::string>	_parameters; // <--------- just to test: greg

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

		std::string	getVerb(void) const; // <--------- just to test: greg
		void		setVerb(std::string str); // <--------- just to test: greg
		std::vector<std::string> getParameters(void) const; // <--------- just to test: greg
};

#endif
