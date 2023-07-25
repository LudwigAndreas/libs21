//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/PropertiesPatternConverter.h"

namespace s21::parse {

s21::parse::PropertiesPatternConverter::PropertiesPatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Properties";
}

std::shared_ptr<PatternConverter> PropertiesPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<PropertiesPatternConverter>(options);
    return def;
  }
  return std::make_shared<PropertiesPatternConverter>(options);
}

void PropertiesPatternConverter::format(const LoggingEvent &event,
                                        String &to_append_to) const {
  (void) event;
  to_append_to.append("Properties is not implemented yet");

}

}

