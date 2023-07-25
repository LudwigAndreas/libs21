//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>

#include "logger/parse/converters/FullLocationPatternConverter.h"
#include "logger/parse/converters/PatternConverter.h"

namespace s21::parse {

FullLocationPatternConverter::FullLocationPatternConverter(std::vector<
    String> &options)
    : PatternConverter(options) {
  name_ = "Full file location";
}

std::shared_ptr<PatternConverter> FullLocationPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<FullLocationPatternConverter>(options);
    return def;
  }
  return std::make_shared<FullLocationPatternConverter>(options);
}

void FullLocationPatternConverter::format(const LoggingEvent &event,
                                          String &to_append_to) const {
  to_append_to.append(event.GetFileName());
  to_append_to.append(1, (Char) 0x28);
  to_append_to.append(std::to_string(event.getLine()));
  to_append_to.append(1, (Char) 0x29);
}

}