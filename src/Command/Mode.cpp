#include "Server.hpp"

bool	isValidChan(int fd, std::string &chanName)
{
	Server	*serv = (Server *)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (!chanName.empty())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	if (chanName[0] != '#')
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd), false);
	chanName.erase(0, 1);
	if (serv->GetChan(chanName) == INT_MAX)
		return (_sendResponse(ERR_NOSUCHCHANNEL(cli->GetNickName(), chanName), fd), false);
	Channel	chan = serv->GetAllChans()[serv->GetChan(chanName)];
	if (!chan.get_client(fd))
		return (_sendResponse(ERR_NOTONCHANNEL(cli->GetNickName(), chanName), fd), false);
	if (!chan.get_client(fd))
		return (_sendResponse(ERR_CHANOPRIVSNEEDED(cli->GetNickName(), chanName), fd), false);
	return (true);
}

bool	isGoodParam(int fd, std::string &chanName, std::string &mode, std::string &param)
{
	Server	*serv = (Server *)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (!isValidChan(fd, chanName))
		return (false);
	
	return (true);
}

void	Server::mode_cmd(int fd, std::string cmd)
{
	cmd.erase(0, 4);
	std::string	chanName, modeStr, param, badParam;
	std::stringstream	ss(cmd);
	ss >> chanName >> modeStr >> param >> badParam;
	int mode = 0;
	Client	*cli = GetClient(fd);
	if (!badParam.empty())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	if (!isGoodParam(fd, chanName, modeStr, param))
		return ;
	Channel	chan = this->GetAllChans()[this->GetChan(chanName)];
	/*faire les modes avec un tableau de fonction*/
	switch (modeStr[1])
	{
		case 'i':
			mod_i(fd, chanName , modeStr[0], param);
			break;
		case 't':
			mod_t(fd, chanName , modeStr[0], param);
			break;
		case 'k':
			mod_k(fd, chanName , modeStr[0], param);
			break;
		case 'o':
			mod_o(fd, chanName , modeStr[0], param);
			break;
		case 'l':
			mod_l(fd, chanName , modeStr[0], param);
			break;
		default:
			return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	}
}
