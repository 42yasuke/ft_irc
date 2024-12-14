#include "Server.hpp"

bool	isValidDest(int fd, std::string dest)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (dest.empty())
		return (senderror(411, cli->GetNickName(), fd, " :No recipient given (PRIVMSG)\n"), false);
	if (dest[0] != '#' && !serv->GetClient(dest))
		return (senderror(401, cli->GetNickName(), fd, " :" + dest + " :No such nick\n"), false);
	if (dest[0] == '#' && serv->GetChan(dest.substr(1)) == INT_MAX)
		return (senderror(401, cli->GetNickName(), fd, " :" + dest + " :No such channel\n"), false);
	return (true);
}

bool	isValidMsg(int fd, std::string msg)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (msg.empty())
		return (senderror(412, cli->GetNickName(), fd, " :No text to send\n"), false);
	return true;
}

void	Server::privmsg_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(7);
	std::stringstream ss(cmd);
	std::string dest, msg, tmp;
	ss >> dest;
	while (ss)
	{
		ss >> tmp;
		msg += tmp;
	}
	if (!isValidDest(fd, dest) || !isValidMsg(fd, msg))
		return ;
	if (dest[0] != '#')
	{
		msg = "<" + GetClient(fd)->GetNickName() + "> " + msg + BN;
		_sendResponse(msg, GetClient(dest)->GetFd());
	}
	else
	{
		dest = dest.substr(1);
		size_t	i = 0;
		while (dest != this->channels[i].GetName())
			i++;
		msg = "[#" + dest + "] " + "<" + GetClient(fd)->GetNickName() + "> " + msg + BN;
		this->channels[i].sendToAll_but_not_him(msg, fd);
	}
}
