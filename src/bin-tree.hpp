#include <vector>
#pragma ones

struct NODE {
  int data;
  int file_addr;
  int child_low;
  int child_high;

  int& binary_decide(int target);
};

struct tree {
  std::vector<NODE> nodes;

  void show();
  NODE add_node(int data);
  int find_node(int target);
};
