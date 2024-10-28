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

# define BN "\n"

/* ******************** RPL Macro ******************** */
# define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + BN)
# define RPL_UMODEIS(hostname, channelname, mode, user)  ":" + hostname + " MODE " + channelname + " " + mode + " " + user + BN
# define RPL_CREATIONTIME(nickname, channelname, creationtime) ": 329 " + nickname + " #" + channelname + " " + creationtime + BN
# define RPL_CHANNELMODES(nickname, channelname, modes) ": 324 " + nickname + " #" + channelname + " " + modes + BN
# define RPL_CHANGEMODE(hostname, channelname, mode, arguments) (":" + hostname + " MODE #" + channelname + " " + mode + " " + arguments + BN)
# define RPL_NICKCHANGE(oldnickname, nickname) (":" + oldnickname + " NICK " + nickname + BN)
# define RPL_JOINMSG(hostname, ipaddress, channelname) (":" + hostname + "@" + ipaddress + " JOIN #" + channelname + BN)
# define RPL_NAMREPLY(nickname, channelname, clientslist) (": 353 " + nickname + " @ #" + channelname + " :" + clientslist + BN)
# define RPL_ENDOFNAMES(nickname, channelname) (": 366 " + nickname + " #" + channelname + " :END of /NAMES list" + BN)
# define RPL_TOPICIS(nickname, channelname, topic) (": 332 " + nickname + " #" +channelname + " :" + topic + BN)

/* ******************** IRC Error Macro ******************** */
# define ERR_NEEDMODEPARM(channelname, mode) (": 696 #" + channelname + " * You must specify a parameter for the key mode. " + mode + BN)
# define ERR_INVALIDMODEPARM(channelname, mode) ": 696 #" + channelname + " Invalid mode parameter. " + mode + BN
# define ERR_KEYSET(channelname) ": 467 #" + channelname + " Channel key already set. " + BN
# define ERR_UNKNOWNMODE(nickname, channelname, mode) ": 472 " + nickname + " #" + channelname + " " + mode + " :is not a recognised channel mode" + BN
# define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters." + BN)
# define ERR_CHANNELNOTFOUND(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel" + BN)
# define ERR_NOTOPERATOR(channelname) (": 482 #" + channelname + " :You're not a channel operator" + BN)
# define ERR_NOSUCHNICK(channelname, name) (": 401 #" + channelname + " " + name + " :No such nick/channel" + BN )
# define ERR_INCORPASS(nickname) (": 464 " + nickname + " :Password incorrect !" + BN )
# define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + BN )
# define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + BN )
# define ERR_NICKINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use" + BN)
# define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + BN)
# define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + BN)
# define ERR_CMDNOTFOUND(nickname, command) (": 421 " + nickname + " " + command + " :Unknown command" + BN)

/* ******************** Personal Error Macro ******************** */
# define ERR_BADNICKNAME(nickname) (":" +  nickname + " :bad nickname given" + BN )
# define ERR_BADPARAM(nickname) (":" +  nickname + " :bad parameters given" + BN )

#endif
