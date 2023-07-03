#ifndef CLIENT_HPP
# define CLIENT_HPP

# define DISCONNECTED 1
# define CONNECTED 0

# include "Message.hpp"
# include <string>
# include <map>

class Client {
	private:
		int											_sd;
		bool										_status;
		std::string									_nickname;
		std::string									_username;
		std::string									_realname;
		std::string									_sendBuffer;
		char										_recvBuffer[512];
		std::string									_recvString;
		Message										_recvMessage;

	public:
		Client(int sd = -1);
		Client(const Client &ref);
		Client	&operator=(const Client &rhs);
		~Client(void);

		std::string	getNickname(void) const;
		void		setNickname(std::string newNick);

		void	recvPackets(void);
		void	sendPackets(void);
		void	setStatus(bool status);
		bool	getStatus(void) const;
		Message	&getMessage(void);
		void	parse(void);
};

#endif
