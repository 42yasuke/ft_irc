#include "Server.hpp"
#include "Utils.hpp"

int main(int ac, char** av)
{
	Server ser;
	if (ac != 3)
	{
        std::cout << "Usage: " << av[0] << " <port number> <password>" << std::endl; 
        return 1;
    }
	std::cout << "---- SERVER ----" << std::endl;
	try
	{
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		signal(SIGPIPE, SIG_IGN); // or MSG_NOSIGNAL flag in send() to ignore SIGPIPE on linux systems
		if(!isPortValid(av[1]) || isPasswordValid(av[2]))
		{
            std::cout << "invalid Port number / Password!" << std::endl;
            return 1;
        }
		ser.startServer(std::atoi(av[1]), av[2]);
	}
	catch(const std::exception& e)
	{
		ser.close_fds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
    return 0;
}