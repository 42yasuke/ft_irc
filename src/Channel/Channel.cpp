#include "Channel.hpp"

Channel::Channel()
{
	this->invit_only = 0;
	this->topic = 0;
	this->key = 0;
	this->limit = 0;
	this->topic_restriction = false;
	this->name = "";
	this->topic_name = "";
	char charaters[5] = {'i', 't', 'k', 'o', 'l'};
	for (int i = 0; i < 5; i++)
		modes.push_back(std::make_pair(charaters[i], false));
	this->created_at = "";
}

Channel::~Channel() {}
Channel::Channel(Channel const &src) { *this = src; }

Channel &Channel::operator=(Channel const &src)
{
	if (this != &src)
	{
		this->invit_only = src.invit_only;
		this->topic = src.topic;
		this->key = src.key;
		this->limit = src.limit;
		this->topic_restriction = src.topic_restriction;
		this->name = src.name;
		this->password = src.password;
		this->created_at = src.created_at;
		this->topic_name = src.topic_name;
		this->clients = src.clients;
		this->admins = src.admins;
		this->modes = src.modes;
	}
	return *this;
}

/* ******************** Methods ******************** */
void Channel::add_client(Client *newClient) { clients.push_back(newClient); }
void Channel::add_admin(Client *newClient) { admins.push_back(newClient); }

void Channel::remove_client(int fd)
{
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetFd() == fd)
		{
			clients.erase(it);
			break;
		}
	}
}
void Channel::remove_admin(int fd)
{
	for (std::vector<Client*>::iterator it = admins.begin(); it != admins.end(); ++it)
	{
		if ((*it)->GetFd() == fd)
		{
			admins.erase(it);
			break;
		}
	}
}
bool Channel::change_clientToAdmin(std::string &nick)
{
	size_t i = 0;
	for (; i < clients.size(); i++)
	{
		if (clients[i]->GetNickName() == nick)
			break;
	}
	if (i < clients.size())
	{
		admins.push_back(clients[i]);
		clients.erase(i + clients.begin());
		return true;
	}
	return false;
}

bool Channel::change_adminToClient(std::string &nick)
{
	size_t i = 0;
	for (; i < admins.size(); i++)
	{
		if (admins[i]->GetNickName() == nick)
			break;
	}
	if (i < admins.size())
	{
		clients.push_back(admins[i]);
		admins.erase(i + admins.begin());
		return true;
	}
	return false;
}

//---------------//SendToAll
void Channel::sendTo_all(std::string rpl1)
{
	for (size_t i = 0; i < admins.size(); i++)
		if (send(admins[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
			std::cerr << "send() faild" << std::endl;
	for (size_t i = 0; i < clients.size(); i++)
		if (send(clients[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
			std::cerr << "send() faild" << std::endl;
}
void Channel::sendTo_all_but_not_him(std::string rpl1, int fd)
{
	for (size_t i = 0; i < admins.size(); i++)
	{
		if (admins[i]->GetFd() != fd)
			if (send(admins[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
				std::cerr << "send() faild" << std::endl;
	}
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->GetFd() != fd)
			if (send(clients[i]->GetFd(), rpl1.c_str(), rpl1.size(), 0) == -1)
				std::cerr << "send() faild" << std::endl;
	}
}
//---------------//SendToAll