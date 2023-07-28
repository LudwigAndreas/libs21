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
  std::map<std::string, std::string> properties_;
  std::string file_path_;

  ~PropertiesReader();

  bool updateProperties();

 public:
  PropertiesReader();

  PropertiesReader(const std::string &file_path);

  void SetPath(const std::string &file_path);

  std::map<std::string, std::string> GetProperties();

  std::string GetProperty(const std::string &key);

  void Update();
};
}

#endif //S21_SRC_PROPERTIESREADER_H_
