//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/ShortFileLocationPatternConverter.h"
namespace s21::parse {

ShortFileLocationPatternConverter::ShortFileLocationPatternConverter(
    std::vector<String> &options) : PatternConverter(options) {
  name_ = "Short file location";
}

PatternConverter *ShortFileLocationPatternConverter::newInstance(std::vector<
    String> options) {
  if (options.empty()) {
    static PatternConverter* def = new ShortFileLocationPatternConverter(options);
    return def;
  }
  return new ShortFileLocationPatternConverter(options);
}

void ShortFileLocationPatternConverter::format(const LoggingEvent &event,
                                               String &to_append_to) const {
  to_append_to.append(event.GetShortFileName());
}

}