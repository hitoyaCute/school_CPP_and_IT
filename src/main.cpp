#include <ostream>
#include <string>
#include "tools.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  // first initiate the tree
  tree bin_tree = fetch_file(static_cast<std::string>(argv[1]));


  // process arguments
  std::string arg1 = argv[2];
  if (arg1 == "find") {
    if (argc != 4) {
      throw "option find expect 2 parameters " + std::to_string(argc-1) + " are given";
    }
    std::string arg2 = argv[3];
    int target = string_hash(arg2);
    std::cout << "searching for '" + static_cast<std::string>(argv[3]) + "'" << std::endl;
    int matched = bin_tree.find_node(
      target);
    show_attr(fetch_info(bin_tree.nodes[matched].file_addr, static_cast<std::string>(argv[1])));
    
  } else {
    
  }; 
}

