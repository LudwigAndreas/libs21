//
// Created by Ludwig Andreas on 15.07.2023.
//

#ifndef S21_SRC_PROPERTIESREADER_H_
#define S21_SRC_PROPERTIESREADER_H_

#include <map>
#include <string>

#include "s21.h"
namespace s21 {
class PropertiesReader {
 protected:
  std::map<std::string, std::string> properties;
  std::string file_path;

  ~PropertiesReader();

  bool updateProperties();

 public:
  PropertiesReader();

  PropertiesReader(const std::string &file_path);

  void set_path(const std::string file_path);

  std::map<std::string, std::string> get_properties();

  std::string get_property(const std::string &key);

  void update();
};
}

#endif //S21_SRC_PROPERTIESREADER_H_
