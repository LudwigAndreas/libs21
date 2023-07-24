//
// Created by Ludwig Andreas on 21.07.2023.
//

#include "logger/parse/converters/LiteralPatternConverter.h"

#include <utility>
#include "utils/logger.inc"
namespace s21::parse {

LiteralPatternConverter *LiteralPatternConverter::newInstance(
    const String &literal) {
  if (literal.length() == 1 && literal[0] == 0x20 /* ' ' */) {
    static auto *blank = new LiteralPatternConverter
        (literal);
    return blank;
  }
  return new LiteralPatternConverter(literal);
}

LiteralPatternConverter::LiteralPatternConverter(const String &literal) {
  name_ = literal;
}

void LiteralPatternConverter::format(const LoggingEvent &event,
                                     String &to_append_to) const {
  (void) event;
  to_append_to.append(this->name_);
}
LiteralPatternConverter::LiteralPatternConverter(std::vector<String> &options)
    : PatternConverter(options) {}

PatternConverter *LiteralPatternConverter::newInstance(std::vector<String> options) {
  (void) options;
  return new LiteralPatternConverter("");
}

}
