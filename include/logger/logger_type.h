//
// Created by Ludwig Andreas on 25.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_LOGGER_TYPE_H_
#define S21_INCLUDE_LOGGER_LOGGER_TYPE_H_

#include <ostream>
#include <istream>
#include <string>

namespace s21 {

typedef std::ostream ToStream;
typedef std::istream InStream;
typedef std::string String;
typedef char Char;

namespace diagnostic {

enum class LogLevel {
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Fatal
};
}
}

#endif //S21_INCLUDE_LOGGER_LOGGER_TYPE_H_
