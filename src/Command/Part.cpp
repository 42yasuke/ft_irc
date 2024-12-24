#include "Server.hpp"

bool isGoodParams(int fd, std::string chanList, std::vector<Channel> &cList, std::string reason)
{
	Server *serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client *cli = serv->GetClient(fd);
	if (chanList.empty())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	for (size_t i = 0; i < reason.size(); i++)
	{
		if (i == 0 && reason[i] != ':')
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		if (i && (!isalpha(reason[i]) || reason[i] != ' '))
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	}
	std::string chanName;
	std::stringstream ss(chanList);
	while (std::getline(ss, chanName, ','))
	{
		if (chanName[0] != '#')
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		if (serv->GetChan(chanName) == INT_MAX)
			{_sendResponse(ERR_NOSUCHCHANNEL(cli->GetNickName(), chanName), fd); continue;};
		cList.push_back(serv->GetAllChans()[serv->GetChan(chanName)]);
	}
	return (cList.size() > 0);
}

void	Server::part_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(4);
	std::string chanList, reason;
	std::vector<Channel> cList;
	std::stringstream ss(cmd);
	ss >> chanList;
	std::getline(ss, reason);
	while (!reason.empty() && reason[0] == ' ')
		reason = reason.substr(1);
	if (!isGoodParams(fd, chanList, cList, reason))
		return ;
	Client	*cli = GetClient(fd);
	for (std::vector<Channel>::iterator it = cList.begin(); it != cList.end(); ++it)
	{
		Channel &chan = *it;
		if (!chan.get_client(fd))
			{_sendResponse(ERR_NOTONCHANNEL(cli->GetNickName(), chan.GetName()), fd); continue;}
		chan.sendToAll(RPL_PART(cli->GetNickName(), chan.GetName(), reason));
		chan.remove_client(fd);
		if (!chan.GetClientsNumber())
			this->RemoveChan(chan.GetName());
	}
}
