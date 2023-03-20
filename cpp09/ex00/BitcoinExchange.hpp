#pragma once

#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <sstream>
#include <ctime>

extern std::map<std::string,std::string> data;

int checkLine(const std::string &line);
int readDataFromCsv(std::map<std::string,std::string> &data);
int sti(const std::string& str);
int printLine(std::string line);