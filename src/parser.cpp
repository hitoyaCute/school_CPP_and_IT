// this will parse the .list

#include <fstream>
#include <string>


std::string open_file(std::string dir) {
  std::ifstream list_file(dir);
  if (list_file.is_open()) {
    std::string output;
    
    // read the file idk...
    std::string line;
    while (std::getline(list_file, line)) {
      output += "\n"+line;
    }
    return output;
  } else {
    throw "FileContextError:something went wrong while reading the file";
  }
}

// uhhh parse the .list
void parse() {
  //how to parse stuff on cpp....

}


