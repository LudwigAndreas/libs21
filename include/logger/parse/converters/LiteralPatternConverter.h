//
// Created by Ludwig Andreas on 21.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSE_LITERALPATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSE_LITERALPATTERNCONVERTER_H_

#include "PatternConverter.h"

namespace s21::parse {
class LiteralPatternConverter : public PatternConverter {
 public:

  LiteralPatternConverter(std::vector<String> &options);
  explicit LiteralPatternConverter(const String &literal);

  void format(const LoggingEvent &event, String &to_append_to) const override;

  static std::shared_ptr<PatternConverter> newInstance(std::vector<String> options);

  static std::shared_ptr<PatternConverter> newInstance(const String &literal);
};
}

#endif //S21_INCLUDE_LOGGER_PARSE_LITERALPATTERNCONVERTER_H_
