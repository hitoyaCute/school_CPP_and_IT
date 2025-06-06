// this will parse the .list
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <utility>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "tools.hpp"
#include "parser.hpp"
#include "bin-tree.hpp"

// fetch atributes of the data from the list file...
std::vector<std::pair<std::string, std::string>> fetch_info(int addr, std::string dir) {
  // fetch the file
  std::ifstream file(dir);
  
  if (file.is_open()) {
    // initialization
    int line_id = 0;
    std::string buffer;
    bool reading = false;
    std::vector<std::pair<std::string, std::string>> atributes;

    // itterate over the lines of the input file
    while (std::getline(file, buffer)) {
      if (buffer == "") {
        continue;
      } else if (!reading && line_id == addr) {
        reading = true;
      } else if (reading) {
        if (buffer.at((int)std::size(buffer)-1) == ':') {
          return atributes;
        }

        std::vector<std::string> attr = split_string(buffer, ";");
        
        if ((int)std::size(attr) != 2) {
          throw std::runtime_error {"ParsingError: invalid list file syntax"};
        }
        
        atributes.push_back({attr[0],attr[1]});
      }; line_id ++;
    }
    return atributes;
  } else {
    throw std::runtime_error {"FileContextError: cant open file"};
  }
}

// uhhh parse the .list
tree fetch_file(std::string list_dir) {
  // create vars
  tree bin_tree;
  std::ifstream file(list_dir);
  
  if (!file) {
    throw std::runtime_error {"FileContextError: cant open the file"};
  }
  // find the header then parse and store on the tree
  std::string line;
  int current_line = 0;

  while (std::getline(file, line)) {
    if (line == "") {
      continue;
    // if the line ends with ":"
    } else if (line.at((int)line.size()-1) == ':') {
      line.pop_back(); // remove the last character on the line
      bin_tree.add_node(string_hash(line), current_line); // add the node
      line.clear(); // clear the line for next header
    }; current_line++;
  }
  return bin_tree;
}

// show the attributes
void show_attr(std::vector<std::pair<std::string,std::string>> attr) {
  std::pair<std::string, std::string> attr_holder;
  for (int i = 0; i < (int)std::size(attr); i++) {
    attr_holder = attr[i];
    std::cout << attr_holder.first << ": " << strip(attr_holder.second) << std::endl;
  }
}


