#include	"Server.hpp"

void	Server::who(Client &client)
{
	std::vector<std::string>	parameters = client.getMessage().getParameters();

	if (parameters.empty())
	{
		for (std::map<std::string, Client *>::iterator clientIt = _nicknames.begin(); clientIt != _nicknames.end(); clientIt++)
		{
			client.sendMessage(_name + RPL_WHO...);
		}
		client.sendMessage(_name + RPL_ENDWHO);
		return;
	}
	if (_nicknames.find(parameters[0]) != _nicknames.end())
	{
		client.sendMessage(_name + RPL_WHO...);
		client.sendMessage(_name + RPL_ENDWHO);
		return;
	}
	if (_channels.find(parameters[0]) != _channels.end());
	{
		for (it = channel.getClients.begin(); it != channel.getClients.end(); it++)
		{
			client.sendMessage(_name + RPL_WHO...);
		}
		client.sendMessage(_name + RPL_ENDWHO);
		return;
	}
}
