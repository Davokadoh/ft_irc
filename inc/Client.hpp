#ifndef CLIENT_HPP
#define CLIENT_HPP

#define DISCONNECTED 1
#define CONNECTED    0

#include "Macros.hpp"
#include "Message.hpp"
#include <map>
#include <string>

class Client
{
private:
  int         _sd;
  bool        _rdyToSend;
  bool        _status;       // How about an enum ?
  bool        _isRegistered; // How about an enum ?
  bool        _isPassOK;
  std::string _ip;
  std::string _nickname;
  std::string _username;
  std::string _source;
  std::string _realname;
  std::string _sendBuff;
  char        _recvBuff[512];
  std::string _recvString;
  Message     _recvMessage;

public:
  Client(int sd = -1, const std::string &ip = "0");
  Client(const Client &ref);
  Client &operator=(const Client &rhs);
  ~Client(void);

  std::string getNickname(void) const;
  std::string getUsername(void) const;
  std::string getRealname(void) const;
  std::string getSource(void) const;
  std::string getIp(void) const;
  std::string getSendBuff(void) const;
  bool        getIsRegistered(void) const;
  bool        getIsPassOK(void) const;
  bool        getRdyToSend(void) const;
  void        setNickname(std::string newNick);
  void        setUsername(std::string username);
  void        setRealname(std::string realname);
  void        setSource(std::string source);
  void        setIsRegistered(bool status);
  void        setIsPassOK(bool status);
  void        setRdyToSend(bool status);

  void    recvPackets(void);
  void    sendPackets(void);
  void    setStatus(bool status);
  bool    getStatus(void) const;
  Message getMessage(void) const;
  void    resetMessage(void);
  void    parse(void);
  void    sendMessage(const std::string &msg);
  void    setMessage(std::string part, std::string channel);
};

#endif
