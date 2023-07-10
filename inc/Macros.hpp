#ifndef	MACROS_HPP
# define MACROS_HPP

# define RPL_WELCOME(nickname, servername) " 001 " + nickname + " :Welcome to the " + servername + " Network " + nickname
# define RPL_YOURHOST(nickname, servername) " 002 " + nickname + " :Your host is " + servername
# define RPL_CREATED(nickname) " 003 " + nickname + " :This server was created today"
# define RPL_MYINFO(nickname, servername) " 004 " + nickname + " " + servername
# define RPL_ISUPPORT(nickname) " 005 " + nickname + " JE SAIS PAS"
# define RPL_LUSERCLIENT(nickname, nbrUsers, nbrChannel) " 251 " + nickname + " :There are " + nbrUsers + "  users and 0 invisible on " + nbrChannel + " servers"
# define RPL_NOTOPIC(client, channel) " 331 " + client + " " + channel + " :No topic is set"
# define RPL_TOPIC(client, channel, topic) " 332 " + client + " " + channel + " " + topic
# define RPL_NAMREPLY(channel) " 353 " + channel + " = "
# define RPL_ENDOFNAMES(channel) " 366 " + channel + " :End of /NAMES list"
# define ERR_NOSUCHCHANNEL(client, channel) " 403 " + client + " " + channel  + " :No such channel"
# define ERR_UNKNOWNCOMMAND(nickname) " 421 " + nickname + " :Unknown command"
# define ERR_NOTONCHANNEL(client, channel) " 442 " + client + " " + channel + " :You're not on that channel"
# define ERR_NOTREGISTERED(nickname) " 451 " + nickname + " :You have not registered"
# define ERR_NEEDMOREPARAMS(nickname) " 461 " + nickname + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(nickname) " 462 " + nickname + " :You may not reregister"
# define ERR_CHANOPRIVSNEEDED(client, channel) " 482 " + client + " " + channel + " :You're not channel operator"

#endif
