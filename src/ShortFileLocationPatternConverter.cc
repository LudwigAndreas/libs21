//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/ShortFileLocationPatternConverter.h"
namespace s21::parse {

ShortFileLocationPatternConverter::ShortFileLocationPatternConverter(
    std::vector<String> &options) : PatternConverter(options) {
  name_ = "Short file location";
}

std::shared_ptr<PatternConverter> ShortFileLocationPatternConverter::newInstance(std::vector<
    String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<ShortFileLocationPatternConverter>(options);
    return def;
  }
  return std::make_shared<ShortFileLocationPatternConverter>(options);
}

void ShortFileLocationPatternConverter::format(const LoggingEvent &event,
                                               String &to_append_to) const {
  to_append_to.append(event.GetShortFileName());
}

}