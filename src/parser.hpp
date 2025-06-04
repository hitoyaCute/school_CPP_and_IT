#pragma once
#include <unordered_map>
#include <string>

// for reference
#include "bin-tree.hpp"


std::unordered_map<std::string, std::string> fetch_info(int addr, std::string dir);
tree fetch_file(std::string list_dir);
void show_attr(std::unordered_map<std::string,std::string> attr);


