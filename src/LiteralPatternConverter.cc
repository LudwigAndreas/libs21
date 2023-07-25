//
// Created by Ludwig Andreas on 21.07.2023.
//

#include "logger/parse/converters/LiteralPatternConverter.h"

namespace s21::parse {

std::shared_ptr<PatternConverter> LiteralPatternConverter::newInstance(
    const String &literal) {
  if (literal.length() == 1 && literal[0] == 0x20 /* ' ' */) {
    static std::shared_ptr<LiteralPatternConverter> blank = std::make_shared<LiteralPatternConverter>
        (literal);
    return blank;
  }
  return std::make_shared<LiteralPatternConverter>(literal);
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

std::shared_ptr<PatternConverter> LiteralPatternConverter::newInstance(std::vector<String> options) {
  (void) options;
  return std::make_shared<LiteralPatternConverter>("");
}

}
