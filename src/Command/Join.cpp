#include "Server.hpp"

std::vector<Channel> getChanList(std::string chanList)
{
	Server *serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	std::vector<Channel> chanList_vec;
	std::stringstream ss(chanList);
	std::string chan;
	while (std::getline(ss, chan, ','))
		chanList_vec.push_back(serv->GetAllChans()[serv->GetChan(chan)]);
	return (chanList_vec);
}

std::vector<std::string> getStrList(std::string strList)
{
	std::vector<std::string> strList_vec;
	std::stringstream ss(strList);
	std::string str;
	while (std::getline(ss, str, ','))
		strList_vec.push_back(str);
	return (strList_vec);
}

bool	isValidChan(int fd, std::string chanName, std::string chanPw)
{
	Server	*serv = (Server *)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	Channel chan;
	if (serv->GetChan(chanName) == INT_MAX)
	{
		if (chanName.empty() || chanName.size() > MAX_CHAN_NAME)
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		for (size_t i = 0; i < chanPw.size(); i++)
		{
			if (!isprint(chanPw[i]))
				return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
		}
		chan.SetName(chanName);
		chan.SetPassword(chanPw);
		if (serv->GetAllChans().size() == MAX_CHAN_NB)
			return (_sendResponse(ERR_SERVERFULL_CHAN(cli->GetNickName()), fd), false);
		serv->AddChannel(chan);
	}
	else
	{
		chan = serv->GetAllChans()[serv->GetChan(chanName)];
		if (chan.GetInvitOnly())
		{
			if (!cli->GetInviteChannel(chanName))
				return (_sendResponse(ERR_INVITEONLYCHAN(cli->GetNickName(), chanName), fd), false);
		}
		if (chan.GetClientsNumber() == chan.GetLimit())
			return (_sendResponse(ERR_CHANNELISFULL(cli->GetNickName(), chanName), fd), false);
		if (!chan.GetPassword().empty() && chan.GetPassword() != chanPw)
			return (_sendResponse(ERR_INCORPASS(cli->GetNickName()), fd), false);
		if (chan.get_client(fd))
			return (_sendResponse(ERR_USERONCHANNEL(cli->GetNickName(), chanName), fd), false);
	}
	return (true);
}

bool	isGoodParams(int fd, std::string chanList, std::string chanPw, std::map<std::string, std::string> &chanName_pw)
{
	Server	*serv = (Server *)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	std::vector<std::string> chanList_vec = getStrList(chanList);
	std::vector<std::string> chanPw_vec = getStrList(chanPw);
	if (chanList_vec.size() != chanPw_vec.size())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	if (chanList_vec.size() > MAX_JOIN_CHAN_AT_ONCE)
		return (_sendResponse(ERR_TOOMANYCHANNELS(cli->GetNickName()), fd), false);
	for (size_t i = 0; i < chanList_vec.size(); i++)
	{
		if (chanList_vec[i][0] != '#')
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	}
	for (size_t i = 0; i < chanList_vec.size(); i++)
		chanName_pw.insert(std::make_pair(chanList_vec[i].substr(1), chanPw_vec[i]));
	for (std::map<std::string, std::string>::iterator it = chanName_pw.begin(); it != chanName_pw.end(); it++)
	{
		if (!isValidChan(fd, it->first, it->second))
			chanName_pw.erase(it);
	}
	return (!chanName_pw.empty());
}

void	Server::join_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(4);
	std::string chanList, chanPw, badparam;
	std::stringstream ss(cmd);
	ss >> chanList >> chanPw >> badparam;
	Client	*cli = GetClient(fd);
	if (!badparam.empty())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	std::map<std::string, std::string> chanName_pw;
	if (!isGoodParams(fd, chanList, chanPw, chanName_pw))
		return ;
	for (std::map<std::string, std::string>::iterator it = chanName_pw.begin(); it != chanName_pw.end(); it++)
	{
		Channel chan = GetAllChans()[GetChan(it->first)];
		chan.add_client(cli);
		chan.sendToAll(RPL_JOIN(cli->GetNickName(), it->first));
		if (!chan.GetTopicName().empty())
			_sendResponse(RPL_TOPIC(cli->GetNickName(), it->first, chan.GetTopicName()), fd);
		_sendResponse(RPL_NAMREPLY(cli->GetNickName(), it->first, chan.GetClientList()), fd);
		_sendResponse(RPL_ENDOFNAMES(cli->GetNickName(), it->first), fd);
	}
}
