#include <csignal>
#include <iostream>
#include <ostream>
#include <vector>

struct NODE {
  int child_low  = -1;
  int child_high = -1;
  int file_addr; 
  int data;
  
  // return return address of the chossen child
  int& binary_decide(int target) {
    if (data < target) {
      return child_low;
    } else {
      return child_high;
    }
  }
};

// binary search tree
struct tree {
  std::vector<NODE> nodes;

  int find_node(int target) {
    if (nodes.size() == 0) {
      throw "ValueError: \"you will never find food from a empty freezer\" - meu";
    }
    int current_node = 0;

    while (true) {
      std::cout << "route: " << current_node << std::endl;
      if (nodes[current_node].data == target) {
        // return the address of the matched node
        return current_node;
      } else {

        current_node = nodes[current_node].binary_decide(target);
        if (current_node == -1 || current_node > nodes.size()) {
          throw "Exemption: something went wrong";
        }
      }
    }
  }

  NODE add_node(int data) {
    // create new node sctruct
    NODE node;
    node.data = data;
    
    // the logic that organize the nodes on a binary tree
    // create the mother(of all) node
    if (nodes.size() == 0) {
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
  void show_tree () {
    std::cout << "{";
    for (int i = 0; i < (int)nodes.size(); i++) {
      std::cout << "node_" << i << ": { low: " << nodes[i].child_low << ",high: " << nodes[i].child_high << ",data: " << nodes[i].data << "},";
    }
    std::cout << "}" << std::endl;
  }
};

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







