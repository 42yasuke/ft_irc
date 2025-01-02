#include "Server.hpp"

bool	isGoodParams(int fd, std::string &chanName, std::string &kickList, std::string &reason)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (chanName.empty() || kickList.empty())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	if (chanName[0] != '#')
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	chanName.erase(0, 1);
	if (!reason.empty())
	{
		if (reason[0] != ':')
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		reason = reason.substr(1);
		for (size_t i = 0; i < reason.size(); i++)
			if (!isalpha(reason[i]) && !(reason[i] != ' '))
				return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	}
	if (serv->GetChanID(chanName) == INT_MAX)
		return (_sendResponse(ERR_NOSUCHCHANNEL(cli->GetNickName(), chanName), fd), false);
	Channel	*chan = serv->GetChan(chanName);
	if (chan->get_admin(fd) != cli)
		return (_sendResponse(ERR_CHANOPRIVSNEEDED(cli->GetNickName(), chanName), fd), false);
	size_t i = 0;
	while (i < kickList.size())
	{
		if (!std::isalnum(kickList[i]) && kickList[i] != ',' && kickList[i] != '_')
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		i++;
	}
	return(true);
}

void	ft_fillMykList(int fd, std::string &chanName, std::string &kickList, std::vector<Client*> &kList)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	Channel	*chan = serv->GetChan(chanName);
	std::istringstream stm(kickList);
	std::string line;
	while(std::getline(stm, line, ','))
	{
		Client	*tmp = serv->GetClient(line);
		if (!tmp)
			{_sendResponse(ERR_NOSUCHNICK(line), fd); continue;}
		if (!chan->GetClientInChannel(line))
			{_sendResponse(ERR_NOTONCHANNEL(cli->GetNickName(), chanName), fd); continue;}
		kList.push_back(tmp);
	}
	if (kList.empty())
		_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd);
	else if (kList.size() > MAX_KICK_LIST)
		_sendResponse(ERR_TOOMANYTARGETS(cli->GetNickName()), fd);
}

void	Server::kick_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(4);
	std::string chanName, kickList, reason;
	std::vector<Client*> kList;
	std::stringstream ss(cmd);
	ss >> chanName;
	ss >> kickList;
	std::getline(ss, reason);
	while (!reason.empty() && reason[0] == ' ')
		reason = reason.substr(1);
	if (!isGoodParams(fd, chanName, kickList, reason))
		return ;
	chanName = chanName.substr(1);
	while (!isalnum(reason[0]))
		reason = reason.substr(1);
	ft_fillMykList(fd, chanName, kickList, kList);

	Client	*cli = GetClient(fd);
	Channel	*chan = this->GetChan(chanName);
	for (std::vector<Client*>::iterator it = kList.begin(); it != kList.end(); ++it)
	{
		std::string kickMsg = ":" + cli->getHostname() + " KICK #" + chanName + " " + (*it)->GetNickName() + " :" + reason + BN;
		send((*it)->GetFd(), kickMsg.c_str(), kickMsg.length(), 0);
		chan->sendToAll(kickMsg);
		chan->rmClient((*it)->GetFd());
	}
}
