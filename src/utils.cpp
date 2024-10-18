#include "Utils.hpp"

bool	isPortValid(std::string port)
{
	int	nb;

	if (port.empty())
		return (false);
	for (char c : port)
	{
		if (!isdigit(c))
			return (false);
	}
	if (port.size() > 5 || port.size() < 4)
		return (false);
	nb = std::stoi(port);
	if (nb < PORT_AUTORISAT_MIN || nb > PORT_AUTORISAT_MAX)
		return (false);
	return (true);
}

bool	isPasswordValid(std::string pw)
{
	return (!(pw.empty() || pw.size() > 10));
}

void	ft_error(std::string msg)
{
	std::cout << msg << std::endl;
	Server	*serv = (Server*)getServ(NULL);
	if (!serv)
		delete serv;
	exit(EXIT_FAILURE);
}

void	*getServ(void *p)
{
	static void *ser = NULL;
	if (!ser)
		ser = p;
	return ser;
}
