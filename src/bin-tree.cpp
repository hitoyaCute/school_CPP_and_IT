#include <csignal>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "bin-tree.hpp"

// return return address of the chossen child
int& NODE::binary_decide(int target) {
  if (data > target) {
    return child_low;
  }
  return child_high;
}

// binary search tree
int tree::find_node(int target) {
  if ((int)std::size(nodes) == 0) {
    throw std::runtime_error {"ValueError: \'You cant get a food from an empty freezer\' - meu"};
  }
  int current_node = 0;

  while (true) {
    std::cout << "route: " << current_node << std::endl;
    if (nodes[current_node].data == target) {
      // return the address of the matched node
      return current_node;
    } else {
      current_node = nodes[current_node].binary_decide(target);
      if (current_node == -1 || current_node > (int)std::size(nodes)) {
        this->show_tree();
        throw std::runtime_error {"Exemption: something went wrong while finding a node current_node: " + std::to_string(current_node) + " node_size: " + std::to_string((int)std::size(nodes)) + " target: " + std::to_string(target)};
      }
    }
  }
}

NODE tree::add_node(int data) {
  // create new node sctruct
  NODE node;
  node.data = data;
  
  // the logic that organize the nodes on a binary tree
  // create the mother(of all) node
  if ((int)std::size(nodes) == 0) {
    nodes.push_back(node);
    return node;
  
  } else {
    int* next_node = &nodes[0].binary_decide(data);

    while (true) {
      // if its not the end of the tree
      if (*next_node != -1) {
        next_node = &nodes[*next_node].binary_decide(data);
        
      } // else its the end
      else {
        *next_node = nodes.size();
        nodes.push_back(node);
        
        return node;
      }
    }
  }
}
void tree::show_tree () {
  std::cout << "{";
  for (int i = 0; i < (int)nodes.size(); i++) {
    std::cout << "node_" << i <<
    ": { low: " << nodes[i].child_low <<
    ",high: " << nodes[i].child_high <<
    ",data: " << nodes[i].data << "},";
  }
  std::cout << "}" << std::endl;
}


// int main (int argc, char *argv[]) {
//   tree bin_tree;
//   
//   int d[9] = {8,3,10,1,6,14,4,7,13};
//   for (int i = 0; i < (int)std::size(d); i++) {
//     bin_tree.add_node(d[i]);
//   }
//   
//   int num = bin_tree.find_node(4);

//   std::cout << "node num: " << num << std::endl;
//   bin_tree.show_tree();
// }







