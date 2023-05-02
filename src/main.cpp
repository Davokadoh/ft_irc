#include "Msg.hpp"
#include "Client.hpp"
#include <iostream>

//Reimplement with pointer on functions array
void	execute(Msg &msg)
{
	if (msg.command == "NICK")
		nick(msg);
	else if (msg.command == "USER")
		user(msg);
	else if (msg.command == "JOIN")
		join(msg);
	else if (msg.command == "PRIVMSG")
		privmsg(msg);
	else
		cmd_does_not_exist(msg);
}

void	process(FILE &socket, std::string raw)
{
		Msg	msg;

		msg = parse(raw);

		if (valid_msg(msg))
			execute(msg);
		else
			error("Invalid msg parsed");
}

int	main(void)
{
	std::map<std::string, Channel>	channels;
	std::vector<Client>				clients;
	std::vector<FILE>				sockets;

	/*
	 *
	 * Init server here
	 *
	 */

	sockets[0] = listner; //Need to listen for new connections too!
	for (socket : sockets)
	{
		if (ISSET(socket.socket)) //Read only socket ready to be read
			if (socket == listner)
				new_client();
			else
				process(socket, getMsg()); //need to check what recv returns
	}
}
