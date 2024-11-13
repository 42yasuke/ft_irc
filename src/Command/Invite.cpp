#include "Server.hpp"

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
	
	/*1.veriier la commande*/
	/*1.1verifier le nickname de l'invite*/
	/*1.2 verifier que le channle existe*/
	/*1.3 verifier que l'on est operator*/
	/*2.invite le gars en question, c a dire mettre a jour la liste d'invite*/
}
