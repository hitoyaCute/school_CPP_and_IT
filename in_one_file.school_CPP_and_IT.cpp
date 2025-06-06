#include <cstdio>
#include <vector>
#include <string>
#include <csignal>
#include <fstream>
#include <ostream>
#include <iostream>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <unordered_map>


//====================tools==================//

// the object that will hash the string
std::hash<std::string> hasher;

// wrapper of hasher
int string_hash (std::string inp) {
  return static_cast<int>(hasher(inp));
}

// function that will split a string with a delimiter
std::vector<std::string> split_string(std::string& str, std::string delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}


std::string strip(std::string str) {
    // Remove leading whitespace
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    // Remove trailing whitespace
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());

    return str;
}
//====================tools==================//


//====================bin-tree==================//
struct NODE {
  int data = 0;
  int file_addr;
  int child_low = -1;
  int child_high = -1;

  int& binary_decide(int target);
};

// object that holds the nodes on a tree structure
struct tree {
  std::vector<NODE> nodes;

  void show_tree();
  int find_node(int target);
  NODE add_node(int data, int addr = 0);
};

// return return address of the chossen child
int& NODE::binary_decide(int target) {
  // if data is larget than the target
  // then return the pointer of what ever data is chosen
  if (data > target) {
    return child_low;
  }
  return child_high;
}

// perform the binary search
int tree::find_node(int target) {
  // if tree size is 0, throw a runtime error
  if ((int)std::size(nodes) == 0) {
    throw std::runtime_error {"ValueError: \'You cant get a food from an empty freezer\' - meu"};
  }
  int current_node = 0;
  
  // loop
  while (true) {
    // check if the current node hold the data we want
    if (nodes[current_node].data == target) {
      // return the address of the matched node
      return current_node;
    } else { // search the next branch
      current_node = nodes[current_node].binary_decide(target);
      // debugging pourposes
      if (current_node == -1 || current_node > (int)std::size(nodes)) {
        this->show_tree();
        throw std::runtime_error {"Exemption: something went wrong while finding a node current_node: " + std::to_string(current_node) + " node_size: " + std::to_string((int)std::size(nodes)) + " target: " + std::to_string(target)};
      }
    }
  }
}

// adds node/branch on the tree
NODE tree::add_node(int data, int addr) {
  // create new node sctruct
  NODE node;
  node.data = data;
  node.file_addr = addr;
  
  // the logic that organize the nodes on a binary tree
  // create the mother(of all) node
  if ((int)std::size(nodes) == 0) {
    nodes.push_back(node);
    return node;
  
  } else {
    // get the pointer of the next node
    int* next_node = &nodes[0].binary_decide(data);

    while (true) {
      // if its not the end of the tree
      if (*next_node != -1) {
        // if we are not at the end of the branch we move to next node by passing the pointer as reference
        next_node = &nodes[*next_node].binary_decide(data);
        
      } // else its the end
      else {
        // pass the current size of the node to the pointer of next node
        *next_node = nodes.size();
        nodes.push_back(node); // then add that new node to the vector
        
        return node;
      }
    }
  }
}

// debugging function
void tree::show_tree () {
  std::cout << "{";
  for (int i = 0; i < (int)nodes.size(); i++) {
    std::cout << "node_" << i <<
    ": { low: " << nodes[i].child_low <<
    ",high: " << nodes[i].child_high <<
    ",data: " << nodes[i].data <<
    ",addr: " << nodes[i].file_addr << "},";
  }
  std::cout << "}" << std::endl;
}
//====================bin-tree==================//


//====================parcer==================//

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
//====================parcer==================//

//====================main=================//

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
    std::cout << "searching for '" <<
      static_cast<std::string>(argv[3]) <<
      "' hashed: " << target << std::endl;
    
    // find the index of node that holds target node
    int matched = bin_tree.find_node(target);
    
    int address_of_find_node = bin_tree.nodes[matched].file_addr;

    std::cout << "address is " <<
      address_of_find_node << " matched node is " <<
      matched << std::endl;
    // bin_tree.show_tree(); // for debugging
    // show the attributes
    std::cout << "\n\nfetched informaion about '" <<
      static_cast<std::string>(argv[3]) <<
      "' was following:" << std::endl;
    show_attr(
      fetch_info(
        address_of_find_node,
        static_cast<std::string>(argv[1])
      ));
    
  } else {
    std::runtime_error {"Unknown parameter '" + static_cast<std::string>(argv[2]) + "'"};
  }; 
}


//====================main=================//
