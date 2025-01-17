#include "Server.hpp"

void	Server::send_cmd(int fd, std::string cmd)
{
	cmd.erase(0, 4);
	std::stringstream	ss(cmd);
	std::string	nickname, filename;
	ss >> nickname >> filename;
	if (isGoodParam(fd, nickname, filename))
		return ;
}
