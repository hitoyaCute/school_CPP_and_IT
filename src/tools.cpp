#include <string>
#include <functional>
#include "tools.hpp"

// the object that will hash the string
std::hash<std::string> hasher;

// wrapper of hasher
int string_hash (std::string inp) {
  return static_cast<int>(hasher(inp));
}

// function that will split a string with a delimiter
std::vector<std::string> split_string(std::string& str, std::string delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}


std::string strip(std::string str) {
    // Remove leading whitespace
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    // Remove trailing whitespace
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());

    return str;
}
