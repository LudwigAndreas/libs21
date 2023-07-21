//
// Created by Ludwig Andreas on 21.07.2023.
//

#include "logger/parse/LiteralPatternConverter.h"

#include <utility>
#include "utils/logger.inc"
namespace s21::parse {

void LiteralPatternConverter::format(String &to_append_to) const {
  to_append_to.append(this->name_);
}

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

}
