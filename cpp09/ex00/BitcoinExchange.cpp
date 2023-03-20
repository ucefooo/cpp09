#include "BitcoinExchange.hpp"
/*fix the date if its not in the data base*/
int checkLine(const std::string &line)
{
    unsigned long i = 0;
    if (line.empty())
        return 1;
    while(i<10)
    {
        if ((i == 4 || i == 7) && line[i] != '-')
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return 1;
        }
        else if (!isdigit(line[i]) && i != 4 && i != 7)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return 1;
        }
        i++;
    }
    if (line[i] != ' ' || line[i+1] != '|')
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return 1;
    }
    i = line.find('|',0);
    if (line[++i] != ' ' || (line[++i] != '-' && !isdigit(line[i])))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return 1;
    }

    while(++i < line.size())
    {
        if (line[i] == '.' && !line[i+1])
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return 1;
        }   
        if (!isdigit(line[i]) && line[i] != '.')
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return 1;
        }
    }
    return 0;
}

int readDataFromCsv(std::map<std::string,std::string> &data)
{
    std::ifstream infile(".data.csv");
    if (!infile)
	{
		std::cout << "Error: could not open file :data.csv" << std::endl;
		return 1;
	}
    std::string line;
	std::getline(infile, line);
	if(infile.fail() || infile.eof())
	{
		std::cout << "Error: reading file data.csv" << std::endl;
		return 1;
	}
    while(1)
    {
        std::string line;
		std::getline(infile, line);
		if(infile.fail() && !infile.eof())
		{
			std::cout << "Error: reading file data.csv" << std::endl;
			return 1;
		}
        int i = line.find(',',0);
        if (i == (int)line.npos && !infile.eof())
            return 1;
        data[line.substr(0,i)]=line.substr(i+1);
		if (infile.eof())
    		break;
    }
    infile.close();
    return 0;
}


std::tm strToS(std::string datetime_str) {
    std::tm datetime = {};
    std::istringstream ss(datetime_str);
    char sep;
    ss >> datetime.tm_year >> sep >> datetime.tm_mon >> sep >> datetime.tm_mday ;
    datetime.tm_year -= 1900;
    datetime.tm_mon -= 1;
    return datetime;
}

std::string stoStr(std::tm time)
{
    char buffer[12];
    std::strftime(buffer, 11, "%Y-%m-%d", &time);
    std::string date_str = buffer;
    return date_str;
}

std::tm SubtractDays(std::tm date)
{
    std::time_t time = std::mktime(&date);
    time -= 86400;
    std::tm newDate = *std::localtime(&time);
    return newDate;
}

std::string SubOneDay(std::string date)
{
    std::string newDate;
    newDate = stoStr(SubtractDays(strToS(date)));
    return newDate;
}

int sti(const std::string& str)
{
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

int CheckDate(std::string date)
{
	for (std::map<std::string,std::string>::iterator it = data.begin(); it != data.end(); ++it)
    {
		if (it->first == date)
			return 1;
    }
	return 0;
}

std::string NewDateToGetPrice(std::string date)
{
    for(int i=0;i<4;i++)
    {
	    for (std::map<std::string,std::string>::iterator it = data.begin(); it != data.end(); ++it)
        {
		    if (it->first == date)
			    return it->first;
        }
        date = SubOneDay(date);
    }
    throw std::logic_error("Fatal error date not found.");
    return date;
}

std::string DateInMap(const std::string &date)
{
	if (CheckDate(date))
		return date;
	return NewDateToGetPrice(date);
}

double stringToDouble(const std::string& str)
{
    std::stringstream ss(str);
    double result;
    ss >> result;
    return result;
}

int checkValidDate(const std::string& dateString) {
    std::tm datetime = {};
    int tmp,tmp2;
	tmp = dateString.find('-',0);
	datetime.tm_year = stringToDouble(dateString.substr(0,tmp));
	tmp2 = dateString.find('-',tmp+1);
	datetime.tm_mon = stringToDouble(dateString.substr(tmp+1,tmp2));
	datetime.tm_mday = stringToDouble(dateString.substr(tmp2+1));
    datetime.tm_year -= 1900;
    datetime.tm_mon--;
    std::tm newTime = datetime;
    std::time_t time = std::mktime(&newTime);
    std::tm newDate = *std::localtime(&time);
    return (newDate.tm_year == datetime.tm_year && newDate.tm_mon == datetime.tm_mon && newDate.tm_mday == datetime.tm_mday);
}

int printLine(std::string line)
{
    std::string date,num,value;
    int found=0;
    double val=0;
    found = line.find(' ',0);
    date = line.substr(0,found);
    num = line.substr(found+3);
    try
    {
        value = data[DateInMap(date)];
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    val = stringToDouble(num);
    if (val <= 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return 1; 
    }
    if (val >= 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return 1;
    }
    if (!checkValidDate(date))
    {
        std::cout << "Error: not a valid date." << std::endl;
        return 1;
    }
    std::cout << date << " => " << num << " = " << val * stringToDouble(value) << std::endl;
    return 0;
}