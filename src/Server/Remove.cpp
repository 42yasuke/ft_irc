#include "Server.hpp"

void	RmChannels(int fd)
{
	Server	*serv = (Server*)getServ(NULL);
	std::vector<Channel>	chanList = serv->GetAllChans();
	std::string	nick = serv->GetClient(fd)->GetNickName();
	std::string	user = serv->GetClient(fd)->GetUserName();
	for (size_t i = 0; i < chanList.size(); i++)
	{
		int flag = 0;
		if (chanList[i].get_client(fd))
			{chanList[i].remove_client(fd); flag = 1;}
		else if (chanList[i].get_admin(fd))
			{chanList[i].remove_admin(fd); flag = 1;}
		if (chanList[i].GetClientsNumber() == 0)
			{chanList.erase(chanList.begin() + i); i--; continue;}
		if (flag){
			std::string rpl = ":" + nick + "!~" + user + "@localhost QUIT Quit\n";
			chanList[i].sendToAll(rpl);
		}
	}
}

void	Server::RemoveClient(int fd)
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i]->GetFd() == fd)
		{
			this->fds.erase(this->fds.begin() + i);
			RmChannels(fd);
			this->clients.erase(this->clients.begin() + i);
			delete this->clients[i];
			break;
		}
	}
}
