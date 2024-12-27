#include "Server.hpp"

bool	isValidNickAndChan(int fd, std::string nickName, std::string chanName)
{
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	Client	*cli2 = serv->GetClient(nickName);
	if (nickName.empty() || chanName.empty())
		return (senderror(461, "", fd, ERR_BADPARAM(cli->GetNickName())), false);
	if (!cli2)
		return (_sendResponse(ERR_NOSUCHNICK(cli->GetNickName()), fd), false);
	if (serv->GetChan(chanName.substr(1)) == INT_MAX)
		return (_sendResponse(ERR_NOSUCHCHANNEL(cli->GetNickName(), chanName.substr(1)), fd), false);
	Channel chan = serv->GetAllChans()[serv->GetChan(chanName.substr(1))];
	if (!chan.get_client(fd))
		return (_sendResponse(ERR_NOTONCHANNEL(cli->GetNickName(), chanName.substr(1)), fd), false);
	if (chan.GetInvitOnly() && !chan.get_admin(fd))
		return (_sendResponse(ERR_CHANOPRIVSNEEDED(cli->GetNickName(), chanName.substr(1)), fd), false);
	if (chan.GetClientInChannel(nickName))
		return (_sendResponse(ERR_USERONCHANNEL(nickName, chanName.substr(1)), fd), false);
	return (!cli2->GetInviteChannel(chanName));
}

void	Server::invite_cmd(int fd, std::string cmd)
{
	cmd = cmd.substr(6);
	std::string nickName, chanName;
	std::stringstream ss(cmd);
	ss >> nickName;
	ss >> chanName;
	Client	*cli = GetClient(fd);
	if (ss)
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	if (!isValidNickAndChan(fd, nickName, chanName))
		return ;
	Client	*cli2 = GetClient(nickName);
	cli2->AddChannelInvite(chanName);
	_sendResponse(RPL_INVITING(nickName, chanName), fd);
	_sendResponse(RPL_INVITING(cli->GetNickName(), chanName), cli2->GetFd());
}
