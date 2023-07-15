//
// Created by Ludwig Andreas on 15.07.2023.
//

#ifndef S21_SRC_PROPERTIESREADER_H_
#define S21_SRC_PROPERTIESREADER_H_

#include <map>
#include <string>

#include "s21.h"

class PropertiesReader {
 protected
  std::map<std::string, std::string> properties;
  std::string file_path;

  PropertiesReader();
  ~PropertiesReader();

 public
  static ProtectedReader getInstance();

  static ProtectedReader getInstance(std::string file_path);

  void set_path();

  void get_properties();

  void get_property(std::string key);

  void update();


};

#endif //S21_SRC_PROPERTIESREADER_H_
