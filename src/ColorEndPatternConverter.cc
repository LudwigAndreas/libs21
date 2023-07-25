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

std::shared_ptr<PatternConverter> ColorEndPatternConverter::newInstance(
    std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<ColorEndPatternConverter>(options);
    return def;
  }
  return std::make_shared<ColorEndPatternConverter>(options);
}

void ColorEndPatternConverter::format(const LoggingEvent &event,
                                                  String &to_append_to) const {
  (void) event;
  to_append_to.append("\x1B[0m");
}

}