#include "Server.hpp"

bool	onlyAlphaOrSpace(const std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isalpha(str[i]) && !std::isspace(str[i]))
			return false;
	}
	return true;
}

std::string	getHisUserName(std::string &cmd, std::string nickName, int fd)
{
	std::string ret = "";
	std::vector<std::string> vCmd = Server::splitBySpace(cmd);
	if (vCmd[1] != nickName)
		return (_sendResponse(ERR_BADNICKNAME(nickName), fd), ret);
	if (vCmd[2] != "0" || vCmd[3] != "*")
		return (_sendResponse(ERR_BADPARAM(nickName), fd), ret);
	for (int i = 0; i < vCmd.size(); i++)
	{
		ret += vCmd[i] + " ";
		if (ret.length() > MAX_CHAR)
			break;
	}
	ret.resize(MAX_CHAR);
	if (!onlyAlphaOrSpace(ret))
		{_sendResponse(ERR_BADPARAM(nickName), fd); ret.erase();}
	return ret;
}

void	Server::user_cmd(int fd, std::string cmd)
{
	std::vector<std::string> splited_cmd = splitBySpace(cmd);
	Client *cli = GetClient(fd);
	if(!cli || !cli->getRegistered())
		return (_sendResponse(ERR_NOTREGISTERED(std::string("*")), fd));
	if(splited_cmd.size() != 5)
		return (_sendResponse(ERR_NEEDMOREPARAMS(cli->GetNickName()), fd));
	if (!cli->GetUserName().empty())
		return (_sendResponse(ERR_ALREADYREGISTERED(cli->GetNickName()), fd));
	std::string userName = getHisUserName(cmd, cli->GetNickName(), fd);
	if (!userName.size())
		return ;
	cli->SetUsername(userName);
	cli->setLogedin(true);
	_sendResponse(RPL_CONNECTED(cli->GetNickName()), fd);
}
