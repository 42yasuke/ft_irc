#include "Server.hpp"

void	ft_fillMykList(int fd, std::string kickList, std::vector<Client*> &kList)
{
	
}

void	Server::kick_cmd(int fd, std::string cmd)
{
	/*
	1.recuperer les parametres
	1.1 recuperer le client qui kick
	1.2 recuperer les clients a kick
	1.3 recuperer le canal
	2.verifier les parametres
	2.1 verifier si il a les droits de kick
	2.2 verifier si les clients a kick existe dans le canal
	3. virer les gens du canal
	4. envoyer un message au gens du canal et aux gens expluse
	*/
	cmd = cmd.substr(4);
	std::string chanName, kickList, reason;
	std::vector<Client*> kList;
	std::stringstream ss(cmd);
	ss >> chanName;
	ss >> kickList;
	ss >> reason;
	Client	*cli = GetClient(fd);
	if (ss)
		return (_sendResponse(ERR_BADPARAM(cli->GetNickName()), fd));
	ft_fillMykList(fd, kickList, kList);



	if (!isValidNickAndChan(fd, nickName, chanName))
		return ;
	Client	*cli2 = GetClient(nickName);
	cli2->AddChannelInvite(chanName);
	_sendResponse(RPL_INVITING(nickName, chanName), fd);
	_sendResponse(RPL_INVITING(cli->GetNickName(), chanName), cli2->GetFd());
}
