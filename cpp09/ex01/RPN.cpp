#include "RPN.hpp"

void doCalcul(char ope,std::stack<int> &data)
{
	int first = data.top();
	data.pop();
	int second = data.top();
	data.pop();
	if (ope == '-')
		data.push(second - first);
	else if(ope == '+')
		data.push(second + first);
	else if(ope == '*')
		data.push(second * first);
	else if(ope == '/')
	{
		if (first == 0)
			throw std::logic_error("Error divide 0.");
		data.push(second / first);
	}
}
