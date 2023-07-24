//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>

#include "logger/parse/converters/FullLocationPatternConverter.h"
#include "logger/parse/converters/PatternConverter.h"

namespace s21::parse {

FullLocationPatternConverter::FullLocationPatternConverter(std::__1::vector<
    String> &options)
    : PatternConverter(options) {
  name_ = "Full file location";
}

PatternConverter *FullLocationPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new FullLocationPatternConverter(options);
    return def;
  }
  return new FullLocationPatternConverter(options);
}

void FullLocationPatternConverter::format(const LoggingEvent &event,
                                          String &to_append_to) const {
  to_append_to.append(event.GetFileName());
  to_append_to.append(1, (Char) 0x28);
  to_append_to.append(std::to_string(event.getLine()));
  to_append_to.append(1, (Char) 0x29);
}

}