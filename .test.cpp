


#include <functional>
#include <iostream>
#include <string>
int main (int argc, char *argv[]) {
  std::string text = static_cast<std::string>(argv[1]);
  std::cout << "hashing: " << argv[1] << "\n>> " << std::hash<std::string>{}(text) << std::endl;
  return 0;
}


