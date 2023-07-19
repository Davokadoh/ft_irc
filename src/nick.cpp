#include "Server.hpp"

#define VALID_CHARS "\\[]{}|_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" // Need to check this list

bool isNickValid(const std::string &nick)
{
    return (nick.find_first_not_of(VALID_CHARS) != std::string::npos) ? 1 : 0;
}

bool Server::isNickInUse(const std::string &nick)
{
    return (_nicknames.find(nick) != _nicknames.end()) ? 1 : 0;
}

void Server::nick(Client &client)
{
    if (client.getIsPassOK() == false)
    {
        client.setStatus(DISCONNECTED);
        return;
    }
    std::vector<std::string> p = client.getMessage().getParameters();
    std::string              nickname = "";

    if (p.size() != 0)
    {
        nickname = p[0];
    }

    if (nickname.empty())
    {
        client.sendMessage(this->_name + ERR_NONICKNAMEGIVEN(client.getNickname()));
    }
    else if (isNickValid(nickname))
    {
        client.sendMessage(this->_name + ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
    }
    else if (isNickInUse(nickname))
    {
        client.sendMessage(this->_name + ERR_NICKNAMEINUSE(client.getNickname(), nickname));
    }
    else
    {
        if (client.getNickname() != "*")
        {
            _nicknames.erase(client.getNickname());
        }
        _nicknames.insert(std::make_pair(nickname, &client));
        if (client.getIsRegistered() == true)
        {
            for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
            {
                if (it->second->getClients().find(&client) != it->second->getClients().end())
                {
                    it->second->sendToAll(client.getSource() + " NICK :" + nickname);
                }
            }
            client.sendMessage(client.getSource() + " NICK :" + nickname);
            client.setNickname(nickname);
        }
        else
        {
            client.setNickname(nickname);
            if (client.getUsername() != "" && client.getRealname() != "")
            {
                this->registration(client);
            }
        }
    }
}
