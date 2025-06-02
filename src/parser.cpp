// this will parse the .list
#include <iostream>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <string>
#include <vector>
#include "bin-tree.hpp"
#include "tools.hpp"

// fetch atributes of the data from the list file...
std::unordered_map<std::string, std::string> fetch_info(int addr, std::string dir) {
  std::ifstream file(dir);
  
  if (file.is_open()) {
    int line_id = 0;
    std::string buffer;
    bool reading = false;
    std::unordered_map<std::string, std::string> atributes;

    while (std::getline(file, buffer)) {
      if (!reading && line_id == addr) {
        reading = true;
      } else if (reading) {
        if (buffer.at((int)std::size(buffer)-1) == ':') {
          return atributes;
        }
        std::vector<std::string> attr = split_string(buffer, ";");
        if ((int)std::size(attr) != 2) {
          throw "ParsingError: invalid list file syntax";
        }
        atributes[attr[0]] = attr[1];
      } else if (buffer.at((int)buffer.size()-1) == ':') {
        return atributes;
      }
    }
    return atributes;
  } else {
    throw "FileContextError: cant open file";
  }
}

// uhhh parse the .list
tree fetch_file(std::string list_dir) {
  // create vars
  tree bin_tree;
  std::ifstream file(list_dir);
  if (!file) {
    std::cerr << "FileContextError: cant open the file" << std::endl;
    throw 1;
  }
  
  std::string line;
  while (std::getline(file, line)) {
    if (line.at((int)line.size()-1) == ':') {
      line.pop_back();
      bin_tree.add_node(string_hash(line));
      line.clear();
    }
  }
  return bin_tree;
}

void show_attr(std::unordered_map<std::string,std::string> attr) {
  for (auto i : attr) {
    std::cout << i.first << ":" << strip(i.second) << std::endl;
  }
}


// int main (int argc, char *argv[]) {
//   std::unordered_map<std::string, std::string> attr = fetch_info(0, "test.file");
//   show_attr(attr);
