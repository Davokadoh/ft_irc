#ifndef CLIENT_HPP
# define CLIENT_HPP

# define DISCONNECTED 1
# define CONNECTED 0

# include "Message.hpp"
# include <string>
# include <map>

class Client;

typedef void (Client::*CmdFunc)(Message message);

class Client {
	private:
		static std::map<std::string, CmdFunc>	createMap(void);
		void	nick(Message message);
		int											_sd;
		bool										_status;
		std::string									_nickname;
		std::string									_username;
		std::string									_realname;
		std::string									_sendBuffer;
		char										_recvBuffer[512];
		std::string									_recvString;
		Message										_recvMessage;
		static const std::map<std::string, CmdFunc>	_cmdMap;

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
		void	execute(void);
};

#endif
