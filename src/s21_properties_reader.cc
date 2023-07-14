#include "s21.h"

#include <fstream>
#include <sstream>
#include <map>
#include <iostream>

std::map<std::string, std::string> s21::properties_reader(const std::string &file_path) {
  std::ifstream input_file(file_path);
  if (!input_file.is_open()) {
    return std::map<std::string, std::string>();
  }

  std::map<std::string, std::string> key_value_map;
  std::string line;
  while (std::getline(input_file, line)) {
    size_t equalPos = line.find('=');
    size_t first_sym = line.find_first_not_of(' ');
    if (equalPos != std::string::npos && line[first_sym] != '#') {

      size_t comment_pos = line.find_last_not_of('#') + 1;
      if (comment_pos != std::string::npos)
        line.erase(comment_pos);
      std::cout << line[comment_pos] <<  " " << line << std::endl;

      std::string key = line.substr(0, equalPos);
      std::string value = line.substr(equalPos + 1);

      key.erase(0, first_sym);
      key.erase(key.find_last_not_of(' ') + 1);

      value.erase(0, value.find_first_not_of(' '));
      value.erase(value.find_last_not_of(' ') + 1);

      key_value_map[key] = value;
    }
  }
  input_file.close();
  return key_value_map;
}