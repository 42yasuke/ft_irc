#include "Server.hpp"

std::vector<std::string> split_recivedBuffer(std::string str)
{
	std::vector<std::string> vec;
	std::istringstream stm(str);
	std::string line;
	while(std::getline(stm, line))
		vec.push_back(line);
	return vec;
}

std::vector<std::string> split_cmd(std::string& cmd)
{
	std::vector<std::string> vec;
	std::istringstream stm(cmd);
	std::string token;
	while(stm >> token)
	{
		vec.push_back(token);
		token.clear();
	}
	return vec;
}

std::string get_cmd_type(std::string& cmd)
{
	std::istringstream stm(cmd);
	std::string token;
	return (stm >> token, token);
}

bool Server::notregistered(int fd)
{
	if (!GetClient(fd) || GetClient(fd)->GetNickName().empty() || GetClient(fd)->GetUserName().empty() || GetClient(fd)->GetNickName() == "*"  || !GetClient(fd)->GetLogedIn())
		return false;
	return true;
}

void parse_exec_cmd(std::string &cmd, int fd)
{
	if(cmd.empty())
		return ;
	std::string cmd_type = get_cmd_type(cmd);
	size_t found = cmd.find_first_not_of(" \t\v");
	if(found != std::string::npos)
		cmd = cmd.substr(found);
	if(!cmd_type.empty() && (cmd_type == "BONG" || cmd_type == "bong")) /*faire un pointeur sur fonction qui va appeller le bonne focntion*/
		return;
    if(!cmd_type.empty() && (cmd_type == "PASS" || cmd_type == "pass"))
        client_authen(fd, cmd);
	else if (!cmd_type.empty() && (cmd_type == "NICK" || cmd_type == "nick"))
		set_nickname(cmd,fd);
	else if(!cmd_type.empty() && (cmd_type == "USER" || cmd_type == "user"))
		set_username(cmd, fd);
	else if (!cmd_type.empty() && (cmd_type == "QUIT" || cmd_type == "quit"))
		QUIT(cmd,fd);
	else if(notregistered(fd))
	{
		if (!cmd_type.empty() && (cmd_type == "KICK" || cmd_type == "kick"))
			KICK(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "JOIN" || cmd_type == "join"))
			JOIN(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "TOPIC" || cmd_type == "topic"))
			Topic(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "MODE" || cmd_type == "mode"))
			mode_command(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "PART" || cmd_type == "part"))
			PART(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "PRIVMSG" || cmd_type == "privmsg"))
			PRIVMSG(cmd, fd);
		else if (!cmd_type.empty() && (cmd_type == "INVITE" || cmd_type == "invite"))
			Invite(cmd,fd);
		else if (!cmd_type.empty())
			_sendResponse(ERR_CMDNOTFOUND(GetClient(fd)->GetNickName(),cmd_type),fd);
	}
	else if (!notregistered(fd))
		_sendResponse(ERR_NOTREGISTERED(std::string("*")),fd);
}