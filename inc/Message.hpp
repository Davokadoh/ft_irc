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
		std::string	_hostName;
		std::string	_cmd;
		std::vector<std::string>	_param;
		int			fillIdx;
	public:
		Message(void);
		~Message(void);
		
		std::vector<std::string>	pars;
		
		void	parse(std::string toParse);
		void	splitData(std::string tmp);
		int		checkCmd(std::string toCheck);
		void	fillData(std::string data);
		void	srcSplit(void);

		void	clearParam(void);

		void	printTest(void);
};

# endif