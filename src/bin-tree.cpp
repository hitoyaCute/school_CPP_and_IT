#include <utility>
#include <vector>

struct NODE {
  int child_low = 0;
  int child_high = 0;
  
  int data = 0;
  int index;
  
  int binary_decide(int other_data) {
    if (data < other_data) {
      return child_low;
    } else {
      return child_high;
    }
  }
};

struct tree {
  std::vector<std::pair<int, NODE>> nodes;
  int tree_size = 0;
  void add_node(int data) {
    // create new node sctruct
    NODE node;
    node.data = data;
    tree_size += 1;
    
    // the logic that organize the nodes on a binary tree
    // create the mother(of all) node
    if (tree_size == 0) {
      nodes.push_back({tree_size + 1,node});
      node.index = tree_size + 1;
      
    } else {
      int next_node = nodes[0].second.binary_decide(data);

      while (true) {
        // if its not the end of the tree
        if (next_node != 0) {
        next_node = nodes[next_node].second.binary_decide(data);
        } // else its the end
        else {
          tree_size ++;
          nodes.push_back({tree_size, node});
          break;
        }
      }
    }
  }
};

