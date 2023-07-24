//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/PropertiesPatternConverter.h"

namespace s21::parse {

s21::parse::PropertiesPatternConverter::PropertiesPatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Properties";
}

PatternConverter *PropertiesPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new PropertiesPatternConverter(options);
    return def;
  }
  return new PropertiesPatternConverter(options);
}

void PropertiesPatternConverter::format(const LoggingEvent &event,
                                        String &to_append_to) const {
  (void) event;
  to_append_to.append("Properties is not implemented yet");

}

}

