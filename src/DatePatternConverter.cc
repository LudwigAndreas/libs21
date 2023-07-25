//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>
#include <sstream>
#include <iomanip>

#include "logger/parse/converters/PatternConverter.h"
#include "logger/parse/converters/DatePatternConverter.h"

namespace s21::parse {

DatePatternConverter::DatePatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Date time";
}

std::shared_ptr<PatternConverter> DatePatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<DatePatternConverter>(options);
    return def;
  }
  return std::make_shared<DatePatternConverter>(options);
}

void DatePatternConverter::format(const parse::LoggingEvent &event,
                                  String &to_append_to) const {
 (void) event;
 time_t time = std::time(nullptr);
 auto tm = *std::localtime(&time);
 std::stringstream ss;
 ss << std::put_time(&tm, options_[0].c_str());
 to_append_to.append(ss.str());
}

}