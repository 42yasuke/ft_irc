#include "Server.hpp"

bool	is_validNickname(std::string& nickname)
{
	if(nickname.size() < 1 || nickname.size() > MAX_CHAR)
		return false;
	if (!isalpha(nickname[0]) && nickname[0] != '_')
		return false;
	for(size_t i = 1; i < nickname.size(); i++)
	{
		if(!std::isalnum(nickname[i]) && nickname[i] != '_')
			return false;
	}
	return true;
}


bool	nickNameInUse(std::string &nickname, std::vector<Client*> &clients)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->GetNickName() == nickname)
			return true;
	}
	return false;
}

void Server::nick_cmd(int fd, std::string cmd)
{
	std::string inuse;
	cmd = cmd.substr(4);
	size_t pos = cmd.find_first_not_of("\t\v ");
	if(pos == std::string::npos)
		{_sendResponse(ERR_NOTENOUGHPARAM(std::string("*")), fd); return;}
	cmd = cmd.substr(pos);
	if (!is_validNickname(cmd))
		{_sendResponse(ERR_ERRONEUSNICK(std::string(cmd)), fd); return;}
	else if (nickNameInUse(cmd, this->clients))
		{_sendResponse(ERR_NICKINUSE(std::string(cmd)), fd); return;}
	else
	{
		Client *cli = GetClient(fd);
		if (!cli)
			ft_error("Server::nick_cmd at GetClient(fd) failed");
		if(cli->getRegistered())
		{
			std::string oldnick = cli->GetNickName(); 
			cli->SetNickname(cmd);
			if (cli->GetLogedIn())
			{
				for (size_t i = 0; i < this->channels.size(); i++)
				{
					if (this->channels[i].get_client(fd))
						this->channels[i].sendTo_all_but_not_him(RPL_NICKCHANGE(oldnick,cmd), fd);
				}
				_sendResponse(RPL_NICKCHANGE(oldnick,cmd), fd);
			}
			else
				cli->setLogedin(true);
		}
		else if (cli->getRegistered())
			_sendResponse(ERR_NOTREGISTERED(cmd), fd);
	}
}
