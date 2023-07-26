#include "s21.h"

#include <fstream>
#include <sstream>
#include <map>

//static std::string erase_comment(std::string line, char comment_symbol = '#', size_t start_pos = 0, size_t end_pos = std::string::npos) {
//  size_t comment_pos = line.find(comment_symbol, start_pos);
//  if (comment_pos != std::string::npos && comment_pos < end_pos)
//    line.erase(comment_pos);
//  return line;
//}

std::map<std::string, std::string> s21::properties_reader(const std::string &file_path) {
  static char comment_symb = '#';

  std::ifstream input_file(file_path);
  if (!input_file.is_open()) {
    return std::map<std::string, std::string>();
  }

  std::map<std::string, std::string> key_value_map;
  std::string line;
  while (std::getline(input_file, line)) {
    size_t comment_pos = line.find(comment_symb);
    size_t equalPos = line.find('=', 0);

    // find first symbol after spaces
    size_t first_sym = line.find_first_not_of(' ');
    if (equalPos != std::string::npos && equalPos != first_sym && comment_pos > equalPos) {

      // Split on begin and end
      std::string key = line.substr(0, equalPos);
      std::string value = line.substr(equalPos + 1);

      // Erase spaces in key from begin and end
      key.erase(0, first_sym);
      key.erase(key.find_last_not_of(' ') + 1);

      // Erase spaces in value from begin and end
      value.erase(0, value.find_first_not_of(' '));
      value.erase(value.find_last_not_of(' ') + 1);

      // Erase quotes
      if (value[0] == '\"') {
        value = value.substr(1, value.find_first_of('\"', 1) - 1);
      } else if (comment_pos != std::string::npos) {
        value.erase(comment_pos - key.size() - 1);
        value.erase(value.find_last_not_of(' ') + 1);
      }
      key_value_map[key] = value;
    }
  }
  input_file.close();
  return key_value_map;
}