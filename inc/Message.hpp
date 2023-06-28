#ifndef	MESSAGE_HPP
# define MESSAGE_HPP

#include	<iostream>
#include	<vector>
#include	<string>
#include	<sstream>

class	Message
{
	private:
		std::string	_src;
		std::string	_nick;
		std::string	_user;
		std::string	_hostname;
		std::string	_cmd;
		std::vector<std::string>	_parameters;

	public:
		Message(void);
		~Message(void);

		std::string	getSrc(void) const;
		std::string getNick(void) const;
		std::string	getUser(void) const;
		std::string	getHostname(void) const;
		std::string	getCmd(void) const;
		std::vector<std::string>	getParameters(void) const;

		void	setSrc(std::string str);
		void	setNick(std::string str);
		void	setUser(std::string str);
		void	setHostname(std::string str);
		void	setCmd(std::string str);
		
		void	parse(std::string toParse);
		void	splitData(std::string tmp);
		void	srcSplit(void);

		void	printTest(void);
};

# endif