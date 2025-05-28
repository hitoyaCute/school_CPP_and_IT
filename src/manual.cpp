#include <ostream>
#include <string>
#include <iostream>

void help(std::string option) {
  if (option == "--help") {
    std::cout << "How to use:\n\t" << 
    "";
  } else {
    std::cout << "No option are given" << std::endl;
    help("--help");
  }
}
