#ifndef MACROS_HPP
#define MACROS_HPP

#define RPL_WELCOME(client)       " 001 " + client + " :Welcome to the Ft_irc.42 Network, " + client
#define RPL_YOURHOST(client)      " 002 " + client + " :Your host is Ft_irc.42"
#define RPL_CREATED(client, date) " 003 " + client + " :This server was created " + date
#define RPL_MYINFO(client)        " 004 " + client + " Ft_irc.42"
#define RPL_LUSERCLIENT(client, nbrUsers) \
  " 251 " + client + " :There are " + nbrUsers + "  users and 0 invisible on  1 servers"
#define RPL_LUSEROP(client)                     " 252 " + client + " 0 :operator(s) online" // we do not handle server operator
#define RPL_LUSERCHANNELS(client, nbrChannels)  " 254 " + client + " " + nbrChannels + " :channels formed"
#define RPL_LUSERME(client, nbrClients)         " 255 " + client + " :I have " + nbrClients + " clients and 1 servers"
#define RPL_NOTOPIC(client, channel)            " 331 " + client + " " + channel + " :No topic is set"
#define RPL_TOPIC(client, channel, topic)       " 332 " + client + " " + channel + " " + topic
#define RPL_INVITING(client, target, channel)   " 341 " + client + " " + target + " " + channel
#define RPL_NAMREPLY(client, channel, target)   " 353 " + client + " = " + channel + " " + target
#define RPL_ENDOFNAMES(client, channel)         " 366 " + client + " " + channel + " :End of /NAMES list"
#define RPL_MOTD(client, msg)                   " 372 " + client + " :" + msg
#define RPL_MOTDSTART(client)                   " 375 " + client + " :- Ft_irc.42 Message of the day - "
#define RPL_ENDOFMOTD(client)                   " 376 " + client + " :End of /MOTD command."
#define ERR_NOSUCHNICK(client, target)          " 401 " + client + " " + target + " No such nick/channel"
#define ERR_NOSUCHCHANNEL(client, channel)      " 403 " + client + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(client, channel)   " 404 " + client + " " + channel + " :Cannot send to channel"
#define ERR_NORECIPIENT(client, verb)           " 411 " + client + " :No recipient given " + verb
#define ERR_NOTEXTTOSEND(nickname)              " 412 " + nickname + " :No text to send"
#define ERR_UNKNOWNCOMMAND(nickname, verb)      " 421 " + nickname + " " + verb + " :Unknown command"
#define ERR_NOMOTD(nickname)                    " 422 " + nickname + " :MOTD File is missing"
#define ERR_NONICKNAMEGIVEN(nickname)           " 431 " + nickname + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(nickname, newNick) " 432 " + nickname + " " + newNick + " :Erroneous Nickname"
#define ERR_NICKNAMEINUSE(nickname, newNick)    " 433 " + nickname + " " + newNick + " :Nickname already in use"
#define ERR_USERNOTINCHANNEL(client, nickname, channel) \
  " 441 " + client + " " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(client, channel) " 442 " + client + " " + channel + " :You're not on that channel"
#define ERR_USERONCHANNEL(client, target, channel) \
  " 443 " + client + " " + target + " " + channel + " :is already on channel"
#define ERR_NOTREGISTERED(client)             " 451 " + client + " :You have not registered"
#define ERR_NEEDMOREPARAMS(client, cmd)       " 461 " + client + " " + cmd + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(client)         " 462 " + client + " :You may not reregister"
#define ERR_PASSWDMISMATCH(client)            " 464 " + client + " :Password incorrect"
#define ERR_INVITEONLYCHAN(client, channel)   " 473 " + client + " " + channel + " :Cannot join channel (+i)"
#define ERR_CHANOPRIVSNEEDED(client, channel) " 482 " + client + " " + channel + " :You're not channel operator"

#endif
