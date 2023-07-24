//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/LineLocationPatternConverter.h"

namespace s21::parse {

LineLocationPatternConverter::LineLocationPatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Line";
}

PatternConverter *LineLocationPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new LineLocationPatternConverter(options);
    return def;
  }
  return new LineLocationPatternConverter(options);
}

void LineLocationPatternConverter::format(const LoggingEvent &event,
                                          String &to_append_to) const {
  to_append_to.append(std::to_string(event.getLine()));
}

}
