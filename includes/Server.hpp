#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <cctype>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <fcntl.h>
# include <fstream>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <sstream>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include <vector>

# define RED "\e[1;31m"
# define WHI "\e[0;37m"
# define GRE "\e[1;32m"
# define YEL "\e[1;33m"

# define PASS 0
# define NICK 1
# define USER 2
# define QUIT 3
# define KICK 4
# define JOIN 5
# define TOPIC 6
# define MODE 7
# define PART 8
# define INVITE 9
# define PRIVMSG 10
# define CMDNOTFOUND 11
# define NOTREGISTERED 12

# define PORT_AUTORISAT_MIN 1024
# define PORT_AUTORISAT_MAX 65535

# define MAX_CHAR 9

# include "Channel.hpp"
# include "Client.hpp"
# include "Utils.hpp"

class	Client;
class	Channel;

class Server
{
  private:
	int port;
	int server_fdsocket;
	static bool Signal;
	std::string password;
	std::vector<Client*> clients;
	std::vector<Channel> channels;
	std::vector<struct pollfd> fds;
	struct sockaddr_in add;
	struct sockaddr_in cliadd;
	struct pollfd new_cli;

  public:
	Server();
	~Server();
	Server(Server const &src);
	Server &operator=(Server const &src);

	/* ******************** Getters ******************** */
	int GetFd(void);
	int GetPort(void);
	std::string GetPassword(void);
	Client *GetClient(int fd);
	Client *GetClientNick(std::string nickname);
	Channel *GetChannel(std::string name);
	std::vector<Channel>	Server::GetAllChans(void);

	/* ******************** Setters ******************** */
	void SetFd(int server_fdsocket);
	void SetPort(int port);
	void SetPassword(std::string password);
	void AddClient(Client *newClient);
	void AddChannel(Channel newChannel);
	void AddFds(pollfd newFd);
	void set_sever_socket(void);

	/* ******************** Remove Methods ******************** */
	void RemoveClient(int fd);

	/* ******************** Signal Methods ******************** */
	static void SignalHandler(int signum);

	/* ******************** Server Methods ******************** */
	void startServer(int port, std::string pass);
	void accept_new_client(void);
	void reciveNewData(int fd);

	/* ******************** Parsing Methods ******************** */
	static std::vector<std::string> splitByLine(std::string str);
	static std::vector<std::string> split_cmd(std::string &str);
	void parse_exec_cmd(std::string &cmd, int fd);

	/* ******************** Pass command ******************** */
	void pass_cmd(int fd, std::string cmd);

	/* ******************** Nick command ******************** */
	void set_username(std::string &username, int fd);
	void nick_cmd(int fd, std::string cmd);

	//---------------//Authentification Methods
	

	void ft_display(void);
};

#endif