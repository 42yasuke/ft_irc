#include "Server.hpp"

bool	isGoodParams(int fd, std::string chanList, std::vector<Channel> &cList)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (!chanList.empty())
	{
		cList.clear();
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
	}
	return (true);
}

void	Server::list_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(4);
	std::string chanList;
	std::vector<Channel> cList = this->GetAllChans();
	std::stringstream ss(cmd);
	ss >> chanList;
	if (!isGoodParams(fd, chanList, cList))
		return ;
	Client	*cli = GetClient(fd);
	_sendResponse(RPL_LISTSTART(cli->GetNickName()), fd);
	bool	flag = chanList.empty();
	for (std::vector<Channel>::iterator it = cList.begin(); it != cList.end(); ++it)
	{
		std::stringstream ss;
		ss << it->GetClientsNumber();
		if (!flag)
			_sendResponse(RPL_LIST(cli->GetNickName(), it->GetName(), ss.str(), it->GetTopicName()), fd);
		else
			_sendResponse(RPL_LIST(cli->GetNickName(), it->GetName(), SP, SP), fd);
	}
	_sendResponse(RPL_LISTEND(cli->GetNickName()), fd);
}
