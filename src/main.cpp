#include <ostream>
#include <stdexcept>
#include <string>
#include "tools.hpp"
#include "parser.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  // first initiate the tree
  tree bin_tree = fetch_file(static_cast<std::string>(argv[1]));


  // process arguments
  if (static_cast<std::string>(argv[2]) == "find") {
    if (argc != 4) {
      throw "option 'find' expect 2 parameters " + std::to_string(argc-1) + " are given";
    }
    // hash the argument
    int target = string_hash(static_cast<std::string>(argv[3]));
    std::cout << "searching for '" + static_cast<std::string>(argv[3]) + "' hashed: " << target << std::endl;
    
    // find the index of node that holds target node
    int matched = bin_tree.find_node(target);

    
    int address_of_find_node = bin_tree.nodes[matched].file_addr;


    std::cout << "address is " << address_of_find_node << " matched node is " << matched << std::endl;
    // bin_tree.show_tree(); // for debugging
    // show the attributes
    std::cout << "\n\nfetched informaion about '" << static_cast<std::string>(argv[3]) << "' was following:" << std::endl;
    show_attr(fetch_info(address_of_find_node, static_cast<std::string>(argv[1])));
    
  } else {
    std::runtime_error {"Unknown parameter '" + static_cast<std::string>(argv[2]) + "'"};
  }; 
}

