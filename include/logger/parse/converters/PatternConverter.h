//
// Created by Ludwig Andreas on 21.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_

#include <vector>
#include <memory>

#include "logger/parse/FormattingInfo.h"
#include "logger/parse/LoggingEvent.h"

namespace s21::parse {
class PatternConverter {
 protected:
  std::vector<String> options_;

  String name_;

  PatternConverter() = default;

  PatternConverter(String &name, std::vector<String> &options);

  PatternConverter(const std::vector<String> &options);

 public:

  PatternConverter(const PatternConverter& other) = delete;

  PatternConverter& operator=(const PatternConverter&) = delete;


  virtual void format(const LoggingEvent &event,
                      String &to_append_to) const = 0;

  void setOptions(const std::vector<String> &options);

  void setName(const String &name);

  const std::vector<String> &getOptions() const;

  const String &getName() const;
  virtual ~PatternConverter() = default;
};
}

#endif //S21_INCLUDE_LOGGER_PARSER_PATTERNCONVERTER_H_
