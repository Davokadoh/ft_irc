#ifndef	MACROS_HPP
# define MACROS_HPP

# define RPL_WELCOME(nickname) " 001 " + nickname + " :Welcome to the Ft_irc.42 Network, " + nickname
# define RPL_YOURHOST(nickname) " 002 " + nickname + " :Your host is Ft_irc.42"
# define RPL_CREATED(nickname, date) " 003 " + nickname + " :This server was created " + date
# define RPL_MYINFO(nickname, servername) " 004 " + nickname + " Ft_irc.42"
# define RPL_ISUPPORT(nickname) " 005 " + nickname + " JE SAIS PAS" // a revoir
# define RPL_LUSERCLIENT(nickname, nbrUsers) " 251 " + nickname + " :There are " + nbrUsers + "  users and 0 invisible on  1 servers"
# define RPL_LUSEROP(nickname) " 252 " + nickname + " 0 :operator(s) online" // we do not handle server operator
# define RPL_LUSERCHANNELS(nickname, nbrChannels) " 254 " + nickname + " " + nbrChannels + " :channels formed"
# define RPL_LUSERME(nickname, nbrClients) " 255 " + nickname + " :I have " + nbrClients + " clients and 1 servers"
# define RPL_NOTOPIC(client, channel) " 331 " + client + " " + channel + " :No topic is set"
# define RPL_TOPIC(client, channel, topic) " 332 " + client + " " + channel + " " + topic
# define RPL_NAMREPLY(client, channel, nick) " 353 " + client + " = " + channel + " " + nick
# define RPL_ENDOFNAMES(client, channel) " 366 " + client + " " + channel + " :End of /NAMES list"
# define ERR_NOSUCHCHANNEL(client, channel) " 403 " + client + " " + channel  + " :No such channel"
# define ERR_NOTEXTTOSEND(nickname) " 412 " + nickname + " :No text to send"
# define ERR_UNKNOWNCOMMAND(nickname) " 421 " + nickname + " :Unknown command"
# define ERR_NOMOTD(nickname) " 422 " + nickname + " :MOTD File is missing"
# define ERR_NONICKNAMEGIVEN(nickname) " 431 " + nickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname, newNick) " 432 " + nickname + " " + newNick + " :Erroneous Nickname"
# define ERR_NICKNAMEINUSE(nickname, newNick) " 433 " + nickname + " " + newNick + " :Nickname already in use"
# define ERR_USERNOTINCHANNEL(client, nickname, channel) " 441 " + client + " " + nickname + " " + channel + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(client, channel) " 442 " + client + " " + channel + " :You're not on that channel"
# define ERR_NOTREGISTERED(nickname) " 451 " + nickname + " :You have not registered"
# define ERR_NEEDMOREPARAMS(nickname) " 461 " + nickname + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(nickname) " 462 " + nickname + " :You may not reregister"
# define ERR_CHANOPRIVSNEEDED(client, channel) " 482 " + client + " " + channel + " :You're not channel operator"

#endif
