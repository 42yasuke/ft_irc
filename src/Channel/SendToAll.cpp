#include "Channel.hpp"

/* ******************** SenToAll ******************** */
void Channel::sendToAll(std::string rpl1)
{
	for (size_t i = 0; i < admins.size(); i++)
		if (send(admins[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	for (size_t i = 0; i < clients.size(); i++)
		if (send(clients[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void Channel::sendToAll_but_not_him(std::string rpl1, int fd)
{
	for (size_t i = 0; i < admins.size(); i++)
	{
		if (admins[i]->GetFd() != fd)
			if (send(admins[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
				std::cerr << "send() failed" << std::endl;
	}
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->GetFd() != fd)
			if (send(clients[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
				std::cerr << "send() failed" << std::endl;
	}
}
