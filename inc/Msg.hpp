#ifndef MSG_HPP
# define MSG_HPP

# include "Client.hpp"
# include <list>

struct	Msg
{
	public:
		Client					client;
		std::string				prefix;
		std::string				command;
		std::list<std::string>	params;
};

#endif
