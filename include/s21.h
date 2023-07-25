#ifndef LIBS21_H
#define LIBS21_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "logger/PropertiesReader.h"

namespace s21 {
std::string to_lower(std::string str);

std::string to_upper(std::string str);

std::map<std::string, std::string> properties_reader(const std::string &file_path);

std::vector<std::string> split(std::string s, std::string delimiter);


}

#endif //LIBS21_H
