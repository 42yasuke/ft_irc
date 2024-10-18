#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>

# include "Server.hpp"

class Server;

bool	isPortValid(std::string port);
bool	isPasswordValid(std::string pw);
void	*getServ(void *p);
void	ft_error(std::string msg);

#endif
