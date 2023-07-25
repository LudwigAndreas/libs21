//
// Created by Ludwig Andreas on 22.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSE_CONVERTERS_THREADPATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSE_CONVERTERS_THREADPATTERNCONVERTER_H_

#include "PatternConverter.h"

namespace s21::parse {
class ThreadPatternConverter : public PatternConverter {
 public:

  ThreadPatternConverter(std::vector<String> &options);

  static std::shared_ptr<PatternConverter>newInstance(std::vector<String> options);

  void format(const LoggingEvent &event, String &to_append_to) const override;
  
};
}

#endif //S21_INCLUDE_LOGGER_PARSE_CONVERTERS_THREADPATTERNCONVERTER_H_
