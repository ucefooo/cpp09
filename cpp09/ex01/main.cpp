#include "RPN.hpp"

int main(int c, char **v)
{
	std::stack<int> data;
	if (c != 2)
	{
		std::cout << "Error: enter valid params." << std::endl;
		return 1;
	}
	std::string param = v[1];
	int i=-1;
	
	try
	{
		while(param[++i])
		{
			if (param[i] == ' ')
				continue;
			if (param[i] == '/' || param[i] == '*' || param[i] == '+' || param[i] == '-')
			{
				if (data.size()<2)
					throw std::logic_error("Error no operands valid.");
				doCalcul(param[i],data);
			}
			else if(isdigit(param[i]))
				data.push(param[i] - '0');
			else
				throw std::logic_error("Error invalid char.");
		}
		if (data.size() != 1)
			throw std::logic_error("Error too many dakchi.");
		std::cout << data.top() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}