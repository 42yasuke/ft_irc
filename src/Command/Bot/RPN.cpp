#include "Bot.hpp"

bool	ft_isAnOperation(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' );
}

bool	ft_isAgoodArg(std::string const &str)
{
	int	nb_int = 0;
	int	nb_op = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ')
		{
			if (isdigit(str[i]))
				nb_int++;
			else if (ft_isAnOperation(str[i]))
			{
				nb_op++;
				if (nb_int < nb_op + 1)
					return false;
			}
			else
				return false;
		}
	}
	return (nb_int == nb_op + 1);
}

void	RPN(std::string const &str)
{
	std::stack<int>	myStack;
	if (!ft_isAgoodArg(str))
		throw std::invalid_argument("Error: invalid argument");
	for(size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			if (isdigit(str[i]))
				myStack.push(str[i] - '0');
			else
			{
				int tmp = myStack.top();
				myStack.pop();
				switch (str[i])
				{
					case '+':
						tmp += myStack.top();
						break;
					case '-':
						tmp = myStack.top() - tmp;
						break;
					case '*':
						tmp *= myStack.top();
						break;
					default:
						if (!tmp)
							throw std::logic_error("Error: Division by zero is forbidden");
						tmp = myStack.top() / tmp;
						break;
				}
				myStack.pop();
				myStack.push(tmp);
			}
		}
	}
	std::cout << myStack.top() << std::endl;
}

