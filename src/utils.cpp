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
	if (nb < 1024 || nb > 65535)
		return (false);
	return (true);
}

bool	isPasswordValid(std::string pw)
{
	return (!(pw.empty() || pw.size() > 10));
}
