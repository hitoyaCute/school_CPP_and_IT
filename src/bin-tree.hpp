#pragma once
#include <vector>

struct NODE {
  int data = 0;
  int file_addr;
  int child_low = -1;
  int child_high = -1;

  int& binary_decide(int target);
};

struct tree {
  std::vector<NODE> nodes;

  void show_tree();
  NODE add_node(int data);
  int find_node(int target);
};
