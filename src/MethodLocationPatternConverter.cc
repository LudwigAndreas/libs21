//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/MethodLocationPatternConverter.h"

namespace s21::parse {

s21::parse::MethodLocationPatternConverter::MethodLocationPatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Method location";
}

std::shared_ptr<PatternConverter> MethodLocationPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<MethodLocationPatternConverter>(options);
    return def;
  }
  return std::make_shared<MethodLocationPatternConverter>(options);
}

void MethodLocationPatternConverter::format(const LoggingEvent &event,
                                            String &to_append_to) const {
 to_append_to.append(event.GetMethodName());
}

}