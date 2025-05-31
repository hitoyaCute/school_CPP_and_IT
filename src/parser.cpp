// this will parse the .list

#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "bin-tree.hpp"
#include "tools.hpp"

// get file alr splited by lines
std::vector<std::string> open_file(std::string dir) {
  std::ifstream list_file(dir);
  if (list_file.is_open()) {
    std::vector<std::string> output;
    
    // read the file idk...
    std::string line;
    while (std::getline(list_file, line)) {
      output.push_back(line);
    }
    return output;
  } else {
    throw "FileContextError:something went wrong while reading the file";
  }
}

// fetch atributes of the data from the list file...
std::vector<std::string> fetch_info(int addr, std::string dir) {
  std::ifstream file(dir);
  
}
// uhhh parse the .list
void parse(std::string list_dir) {
  // create vars
  tree bin_tree;
  std::vector<std::string> list = open_file(list_dir);

  for (int line_id = 0; line_id < (int)list.size(); line_id++) {
    std::string line = list[line_id];
    int len = (int)std::size(line);
    
    if (line.at(len-1) == ':') {
      line.resize(len-1);
      int name = str_to_int(line);
      NODE node = bin_tree.add_node(name);
      node.file_addr = line_id;
      line.clear();
    }
  }
}













