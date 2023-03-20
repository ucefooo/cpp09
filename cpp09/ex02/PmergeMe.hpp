#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <cctype>
#include <sys/time.h>


int checkParam(std::vector<std::size_t> &my,char **v);
void mergeInsertionSortVector(std::vector<std::size_t> &v);
void mergeInsertionSortDeque(std::deque<std::size_t> &v);
