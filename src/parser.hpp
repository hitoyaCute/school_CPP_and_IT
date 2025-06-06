#pragma once
#include <string>
#include <vector>

// for reference
#include "bin-tree.hpp"


tree fetch_file(std::string list_dir);
void show_attr(std::vector<std::pair<std::string,std::string>> attr);
std::vector<std::pair<std::string, std::string>> fetch_info(int addr, std::string dir);


