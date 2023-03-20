#include "PmergeMe.hpp"

int main(int c,char **v)
{
    std::vector<std::size_t> vecParam;

    if (checkParam(vecParam,v))
        return 1;
    std::deque<std::size_t> deqParam(vecParam.begin(),vecParam.end());
    timeval tv;
    long long beforeVec,afterVec,beforeDeque,afterDeque;
    std::cout << "Before: ";
    for(int i =0;i<(int)vecParam.size();i++)
        std::cout << vecParam[i] << " ";
    std::cout << std::endl;
/***************vector***************************************/
    gettimeofday(&tv, NULL);
    beforeVec = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
    mergeInsertionSortVector(vecParam);
    gettimeofday(&tv, NULL);
    afterVec = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
/*************deque*****************************/
    gettimeofday(&tv, NULL);
    beforeDeque = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
    mergeInsertionSortDeque(deqParam);
    gettimeofday(&tv, NULL);
    afterDeque = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
/***********printing********************************/

    std::cout << "After: ";
    for(int i =0;i<(int)vecParam.size();i++)
        std::cout << vecParam[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vecParam.size() << " elements with std::vector : " << afterVec-beforeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deqParam.size() << " elements with std::deque : " << afterDeque-beforeDeque << " us" << std::endl;
    return c-c;
}