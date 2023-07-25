//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>

#include "logger/parse/converters/PatternConverter.h"
#include "logger/parse/converters/ColorEndPatternConverter.h"
namespace s21::parse {

ColorEndPatternConverter::ColorEndPatternConverter(std::vector<
    String> &options)
    : PatternConverter(options) {
  name_ = "Color End";
}

PatternConverter *ColorEndPatternConverter::newInstance(
    std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new ColorEndPatternConverter(options);
    return def;
  }
  return new ColorEndPatternConverter(options);
}

void ColorEndPatternConverter::format(const LoggingEvent &event,
                                                  String &to_append_to) const {
  (void) event;
  to_append_to.append("\x1B[0m");
}

}