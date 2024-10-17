#include "Server.hpp"

/* ******************** Getters ******************** */
int Server::GetPort(void)
{
	return (this->port);
}

int Server::GetFd(void)
{
	return (this->server_fdsocket);
}

std::string Server::GetPassword(void)
{
	return (this->password);
}

Client *Server::GetClient(int fd)
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i].GetFd() == fd)
			return (&this->clients[i]);
	}
	return (NULL);
}

Client *Server::GetClientNick(std::string nickname)
{
	for (size_t i = 0; i < this->clients.size(); i++)
	{
		if (this->clients[i].GetNickName() == nickname)
			return (&this->clients[i]);
	}
	return (NULL);
}

Channel *Server::GetChannel(std::string name)
{
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].GetName() == name)
			return (&channels[i]);
	}
	return (NULL);
}

/* ******************** Setters ******************** */
void Server::SetFd(int fd)
{
	this->server_fdsocket = fd;
}

void Server::SetPort(int port)
{
	this->port = port;
}

void Server::SetPassword(std::string password)
{
	this->password = password;
}

void Server::AddClient(Client newClient)
{
	this->clients.push_back(newClient);
}

void Server::AddChannel(Channel newChannel)
{
	this->channels.push_back(newChannel);
}

void Server::AddFds(pollfd newFd)
{
	this->fds.push_back(newFd);
}

void Server::set_sever_socket()
{
	int en = 1;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(port);
	server_fdsocket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fdsocket == -1)
		throw(std::runtime_error("faild to create socket"));
	if(setsockopt(server_fdsocket, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(server_fdsocket, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(server_fdsocket, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(server_fdsocket, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));
	new_cli.fd = server_fdsocket;
	new_cli.events = POLLIN;
	new_cli.revents = 0;
	fds.push_back(new_cli);
}
