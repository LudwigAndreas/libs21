//
// Created by Ludwig Andreas on 19.07.2023.
//

#ifndef S21_SRC_PATTERNPARSER_H_
#define S21_SRC_PATTERNPARSER_H_

#include <vector>
#include <map>

#include "logger/Logger.h"

namespace s21::parse {
class PatternParser {
 private:
  static const Char ESCAPE_CHAR;

  enum {
    LITERAL_STATE = 0,
    CONVERTER_STATE = 1,
    DOT_STATE = 3,
    MIN_STATE = 4,
    MAX_STATE = 5
  };

  PatternParser();

 public:
  static std::vector<String> parse(const String &pattern);
};
}

#endif //S21_SRC_PATTERNPARSER_H_
