//
// Created by Ludwig Andreas on 25.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSE_CONVERTERS_PIDPATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSE_CONVERTERS_PIDPATTERNCONVERTER_H_

#include "PatternConverter.h"
#include "logger/logger_type.h"

namespace s21::parse {

class PidPatternConverter : PatternConverter {
 public:

  PidPatternConverter(std::vector<String> &options);

  static std::shared_ptr<PatternConverter> newInstance(std::vector<String> options);

  virtual void format(const LoggingEvent &event, String &to_append_to) const override;

};
}

#endif //S21_INCLUDE_LOGGER_PARSE_CONVERTERS_PIDPATTERNCONVERTER_H_
