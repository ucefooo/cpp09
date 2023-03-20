#include "BitcoinExchange.hpp"

std::map<std::string,std::string> data;

int main(int c,char **v)
{
	if (c != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	std::ifstream infile(v[1]);
	if (!infile)
	{
		std::cout << "Error: could not open file " << v[1] << std::endl;
		return 1;
	}
	if (readDataFromCsv(data) || data.size() <= 0)
	{
		std::cout << "Error: reading file data.csv" << std::endl;
		return 1;
	}
	data.erase(data.begin());
	std::string line;
	std::getline(infile, line);
	if (line.empty())
		return 1;
	if(infile.fail())
	{
		std::cout << "Error: reading file" << std::endl;
		return 1;
	}
	while (1)
	{
		std::string line;
		std::getline(infile, line);
		if (line.empty() && !infile.eof())
		{	
			std::cout << "Error: empty line" << std::endl;
			continue;
		}
		else if (line.empty() && infile.eof())
		{
			break;
		}
		if(infile.fail())
		{
			std::cout << "Error: reading file" << std::endl;
			break;
		}
		if (checkLine(line))
			continue;
		if (printLine(line))
			continue;
		if (infile.eof())
    		break;
	}
    infile.close();
	return 0;
}
