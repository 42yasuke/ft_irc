#include "Server.hpp"

void	RmThisFdFromAllChans(int fd, std::string reason)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client *cli = serv->GetClient(fd);
	std::vector<Channel> AllChan = serv->GetAllChans();
	for (std::vector<Channel>::iterator it = AllChan.begin(); it != AllChan.end(); it++)
	{
		if (it->get_client(fd))
			{it->rmClient(fd); it->sendToAll(RPL_QUIT(cli->GetNickName(), reason));}
	}
}

void	Server::RemoveClient(int fd, std::string reason)
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i]->GetFd() == fd)
		{
			this->fds.erase(this->fds.begin() + i);
			RmThisFdFromAllChans(fd, reason);
			this->clients.erase(this->clients.begin() + i);
			delete this->clients[i];
			break;
		}
	}
}

void	Server::RemoveChan(std::string chanName)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].GetName() == chanName)
		{
			this->channels.erase(this->channels.begin() + i);
			break;
		}
	}
}