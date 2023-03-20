#include "PmergeMe.hpp"


std::vector<std::string> split(const std::string& s, char del) {
    std::vector<std::string> vec;
    std::string str;
    std::istringstream inStream(s);
    
    while (std::getline(inStream, str, del))
    {
        if (!str.empty())
            vec.push_back(str);
    }
    return vec;
}

std::vector<std::string> ParseParam(char **v)
{
    int i=0;
    std::string str = "";
    while(v[++i])
    {
        std::string tmp = v[i];
        str=str+tmp+" ";
    }
    std::vector<std::string> vec(split(str,' '));
    return vec;
}

std::size_t stringToInt(const std::string& str)
{
    std::stringstream ss(str);
    std::size_t result;
    ss >> result;
    return result;
}

int checkParam(std::vector<std::size_t> &my,char **v)
{
	std::vector<std::string> vec(ParseParam(v));
	for(int i = 0;i < (int)vec.size();i++)
	{
		std::string tmp = vec[i];
		for(int j =0;j < (int)tmp.size();j++)
		{
			if (!isdigit(tmp[j]))
			{
				std::cout << "Error in params." << std::endl;
				return 1;
			}
		}
	}
	for(int i = 0;i < (int)vec.size();i++)
		my.push_back(stringToInt(vec[i]));
	return 0;
}

void mergeVector(std::vector<std::size_t> &v,std::vector<std::size_t> &left,std::vector<std::size_t> &right)
{
    int leftSize = left.size();
    int rightSize = right.size();
    int i=0,j=0,k=0;

    while(i<leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
            v[k]=left[i++];
        else
            v[k]=right[j++];
        k++;
    }
    while(i<leftSize)
        v[k++]=left[i++];
    while(j<rightSize)
        v[k++]=right[j++];
}

void mergeSortVector(std::vector<std::size_t> &v)
{
    int size = (int)v.size();
    if (size < 8)
        return;
    int midIndex = size/2;
    std::vector<std::size_t> left(v.begin(),v.begin()+midIndex);
    std::vector<std::size_t> right(v.begin()+midIndex,v.end());
    mergeSortVector(left);
    mergeSortVector(right);
    mergeVector(v,left,right);

}

void insertionSortVector(std::vector<std::size_t> &v)
{
    for (int i =1;i < (int)v.size();i++)
    {
        std::size_t curVal = v[i];
        int j = i-1;
        while(j>=0 && v[j] > curVal)
        {
            v[j+1] = v[j];
            j--;
        }
        v[j+1]=curVal;
    }
}

void mergeInsertionSortVector(std::vector<std::size_t> &v)
{
    mergeSortVector(v);
    insertionSortVector(v);
}
/******deque********/
void mergeDeque(std::deque<std::size_t> &v,std::deque<std::size_t> &left,std::deque<std::size_t> &right)
{
    int leftSize = left.size();
    int rightSize = right.size();
    int i=0,j=0,k=0;

    while(i<leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
            v[k]=left[i++];
        else
            v[k]=right[j++];
        k++;
    }
    while(i<leftSize)
        v[k++]=left[i++];
    while(j<rightSize)
        v[k++]=right[j++];
}

void mergeSortDeque(std::deque<std::size_t> &v)
{
    int size = (int)v.size();
    if (size < 8)
        return;
    int midIndex = size/2;
    std::deque<std::size_t> left(v.begin(),v.begin()+midIndex);
    std::deque<std::size_t> right(v.begin()+midIndex,v.end());
    mergeSortDeque(left);
    mergeSortDeque(right);
    mergeDeque(v,left,right);

}

void insertionSortDeque(std::deque<std::size_t> &v)
{
    for (int i =1;i < (int)v.size();i++)
    {
        std::size_t curVal = v[i];
        int j = i-1;
        while(j>=0 && v[j] > curVal)
        {
            v[j+1] = v[j];
            j--;
        }
        v[j+1]=curVal;
    }
}

void mergeInsertionSortDeque(std::deque<std::size_t> &v)
{
    mergeSortDeque(v);
    insertionSortDeque(v);
}