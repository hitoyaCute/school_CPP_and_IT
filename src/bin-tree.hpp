#pragma once
#include <vector>

// object that hold node and its data like the branches, its data and the line where to find the data
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


