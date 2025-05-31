#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>

struct NODE {
  int val1;
  int val2;

  int& get_dat(int dat) {
    if (val1 == dat) {
      return val1;
    } else {
      return val2;
    }
  }
};

int dmain (int argc, char *argv[]) {
  NODE node;
  node.val1 = 1;
  node.val2 = 2;
  int val = atoi(argv[1]);
  int& ref = node.get_dat(val);
  std::cout << "ref: " << ref << std::endl;
  ref = 32;
  std::cout << "vals: " << node.val1 << ", " << node.val2 << std::endl;
  std::cout << "ref: " << node.get_dat(val)+1 << std::endl;
  std::cout << "vals: " << node.val1 << ", " << node.val2 << std::endl;
  return 0;
}



struct Obj{
  int data1 = 1;
  int data2 = 2;
  int& do_stuff(bool val) {
    if (val == true) {
      return data1;
    }
    return data2;
  }
  void show(std::string name = "NoName") {
    std::cout << name << " data1: " << data1 << " data2: " << data2 << std::endl;
  }
};

int main (int argc, char *argv[]) {
  // create 2 object
  Obj obj;
  Obj obj2;
  
  obj.show("obj"); // 1,2
  obj2.show("obj2"); // 1,2
  // get the reference of the data2 atr of obj
  int* dat = &obj.do_stuff(false);
  *dat = 23; // change it
  obj.show("obj"); // 1,23
  obj2.show("obj2"); // 1,2

  // reassigning existing var is not allowed....
  dat = &obj2.do_stuff(true); // get the data1 atr of obj2
  *dat = 0; // change it
  obj.show("obj"); // 1,23
  obj2.show("obj2"); // 0,2
  // but what i get is fking
  // 1,0
  // 1,2
  // wtf???
 
  return 0;
}







#include <csignal>
#include <iostream>
#include <ostream>
#include <vector>

struct NODE {
  int child_low  = -1;
  int child_high = -1;
  
  int data = 0;
  
  // return return address of the chossen child
  int& binary_decide(int target) {
    try {
      if (data < target) {
        return child_low;
      } else {
        return child_high;
      }
    } catch (int error) {
      std::cout << data << ' ' << target << std::endl;
      throw "err";
    };
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
      if (nodes[current_node].data == target) {
        return current_node;
      } else {
        current_node = nodes[current_node].binary_decide(target);
        if (current_node == -1 || current_node > static_cast<int>(nodes.size())) {
          throw "Exemption: something went wrong";
        }
      }
    }
  }

  void add_node(int data) {
    // create new node sctruct
    NODE node;
    node.data = data;

    if (nodes.size() == 0) {
      nodes.push_back(node);
      return;
      
    } else {
      int* next_node = &nodes[0].binary_decide(data);

      while (true) {
        // if its not the end of the tree
        if (*next_node != -1) {
          next_node = &nodes[*next_node].binary_decide(data);
          
        }
        else {
          nodes.push_back(node);
          
          break;
        }
      }
    }
  }
};

int main (int argc, char *argv[]) {
  tree bin_tree;
  
  int d[9] = {8,3,10,1,6,14,4,7,13};
  for (int i = 0; i <= 8; i++) {
    bin_tree.add_node(d[i]);
  }

  std::cout << "node num: " << bin_tree.find_node(14) << std::endl;
  return 0;
}















