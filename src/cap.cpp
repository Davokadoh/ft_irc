#include "Server.hpp"

void Server::cap(Client &client)
{
  if (client.getMessage().getParameters().empty())
  {
    client.sendMessage(this->_name + " CAP :No protocol extensions");
    return;
  }
  else if (client.getMessage().getParameters()[0] == "LS")
  {
    client.sendMessage(this->_name + " CAP * LS :No protocol extensions");
    return;
  }
  else
  {
    client.sendMessage(this->_name + " CAP :No protocol extensions");
    return;
  }
}
