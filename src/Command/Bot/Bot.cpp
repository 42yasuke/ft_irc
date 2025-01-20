#include "Bot.hpp"

bool	isGoodParam(int fd, std::string type, std::string param)
{
	Server	*serv = (Server *)getServ(NULL);
	if (!serv)
		ft_error("getServ failed");
	Client	*cli = serv->GetClient(fd);
	if (type.empty() ||(type == "RPN" && param.empty()))
		return (_sendResponse(ERR_NEEDMOREPARAMS(cli->GetNickName()), fd), false);
	if (type == "jokes")
	{
		std::ifstream file(JOKES_PATH);
		if (!file.good())
			return (_sendResponse(ERR_FILENOTFOUND(std::string(JOKES_PATH)), fd), false);
		file.close();
	}
	//vehrifier les params de PRN
	
	return (true);
}

void	Server::bot_cmd(int fd, std::string cmd)
{
	Client	*cli = GetClient(fd);
	std::ifstream	file(".bonus");
	if (!file.good())
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	cmd.erase(0, 4);
	std::stringstream	ss(cmd);
	std::string	type, param;
	ss >> type;
	getline(ss, param);

	
	if (isGoodParam(fd, type, param))
		return ;
	_sendResponse("Preparing to send file..._\r\n", fd);
	if (!sendFile(fd, type, param))
		return ;
	_sendResponse("File sent successfully\r\n", fd);
}
