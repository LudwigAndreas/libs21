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
  if (options.empty()) {
    date_time_format = "%Y/%m/%d.%X";
  } else {
    date_time_format = options[0];
  }
}

PatternConverter *DatePatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new DatePatternConverter(options);
    return def;
  }
  return new DatePatternConverter(options);
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