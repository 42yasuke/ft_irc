#include "Server.hpp"

void	Server::pass_cmd(int fd, std::string cmd)
{
	Client *cli = GetClient(fd);
	cmd = cmd.substr(4);
	size_t pos = cmd.find_first_not_of("\t\v ");
	if (pos == std::string::npos)
		{_sendResponse(ERR_NOTENOUGHPARAM(std::string("*")), fd); return;}
	cmd = cmd.substr(pos);
	if (!cli->getRegistered())
	{
		if (cmd == password)
			cli->setRegistered(true);
		else
			_sendResponse(ERR_INCORPASS(std::string("*")), fd);
	}
	else
		_sendResponse(ERR_ALREADYREGISTERED(GetClient(fd)->GetNickName()), fd);
}
