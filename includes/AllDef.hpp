#ifndef ALLDEF_HPP
# define ALLDEF_HPP

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

/* ******************** Colors Macro ******************** */
# define RED "\e[1;31m"
# define WHI "\e[0;37m"
# define GRE "\e[1;32m"
# define YEL "\e[1;33m"

/* ******************** Command Macro ******************** */
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
# define MAX_CHAR_TRONC 20
# define MAX_CMD_LENGTH 512

# define BN "\n"

/* ******************** RPL Macro ******************** */
# define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + BN)
# define RPL_UMODEIS(hostname, channel, mode, user)  ":" + hostname + " MODE " + channel + " " + mode + " " + user + BN
# define RPL_CREATIONTIME(nickname, channel, creationtime) ": 329 " + nickname + " #" + channel + " " + creationtime + BN
# define RPL_CHANNELMODES(nickname, channel, modes) ": 324 " + nickname + " #" + channel + " " + modes + BN
# define RPL_CHANGEMODE(hostname, channel, mode, arguments) (":" + hostname + " MODE #" + channel + " " + mode + " " + arguments + BN)
# define RPL_NICKCHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + BN)
# define RPL_JOINMSG(hostname, ipaddress, channel) (":" + hostname + "@" + ipaddress + " JOIN #" + channel + BN)
# define RPL_NAMREPLY(nickname, channel, clientslist) (": 353 " + nickname + " @ #" + channel + " :" + clientslist + BN)
# define RPL_ENDOFNAMES(nickname, channel) (": 366 " + nickname + " #" + channel + " :END of /NAMES list" + BN)
# define RPL_TOPICIS(nickname, channel, topic) (": 332 " + nickname + " #" +channel + " :" + topic + BN)
# define RPL_INVITING(nickname, channel) (": 341 " + nickname + " :has been successfuly invited to #" + channel + BN)

/* ******************** IRC Error Macro ******************** */
# define ERR_NEEDMODEPARM(channel, mode) (": 696 #" + channel + " * You must specify a parameter for the key mode. " + mode + BN)
# define ERR_INVALIDMODEPARM(channel, mode) ": 696 #" + channel + " Invalid mode parameter. " + mode + BN
# define ERR_KEYSET(channel) ": 467 #" + channel + " Channel key already set. " + BN
# define ERR_UNKNOWNMODE(nickname, channel, mode) ": 472 " + nickname + " #" + channel + " " + mode + " :is not a recognised channel mode" + BN
# define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters." + BN)
# define ERR_NOSUCHCHANNEL(nickname, channel) (": 403 " + nickname + " #" + channel + " :No such channel" + BN)
# define ERR_NOSUCHNICK(name) (": 401 " + name + " :No such nick" + BN )
# define ERR_INCORPASS(nickname) (": 464 " + nickname + " :Password incorrect !" + BN )
# define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + BN )
# define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + BN )
# define ERR_NICKINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + BN)
# define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + BN)
# define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + BN)
# define ERR_CMDNOTFOUND(nickname, command) (": 421 " + nickname + " " + command + " :Unknown command" + BN)
# define ERR_NOTONCHANNEL(nickname, channel) (": 442 " + nickname + " #" + channel + " :You're not on that channel" + BN)
# define ERR_CHANOPRIVSNEEDED(nickname, channel) (": 482 " + nickname + " #" + channel + " :You're not channel operator" + BN)
# define ERR_USERONCHANNEL(nickname, channel) (": 443 " + nickname + " #" + channel + " :is already on channel" + BN)

/* ******************** Personal Macro ******************** */
# define RPL_INVITED(nickname, channel) (": " + nickname + " :invite you to #" + channel + BN)
# define ERR_MAXCMDLENGTH(cmd) (":" +  cmd + " :command too long" + BN )
# define ERR_BADNICKNAME(nickname) (":" +  nickname + " :bad nickname given" + BN )
# define ERR_BADPARAM(nickname) (":" +  nickname + " :bad parameters given" + BN )

#endif
