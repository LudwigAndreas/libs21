//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/LineSeparatorPatternConverter.h"

#ifdef _WIN32
#define LOG_EOL "\r\n"
#else
#define LOG_EOL "\n"
#endif

namespace s21::parse {

LineSeparatorPatternConverter::LineSeparatorPatternConverter(std::vector<
    String> &options) : PatternConverter(options) {
  name_ = "Line separator";
}

PatternConverter *LineSeparatorPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new LineSeparatorPatternConverter(options);
    return def;
  }
  return new LineSeparatorPatternConverter(options);
}

void LineSeparatorPatternConverter::format(const LoggingEvent &event,
                                           String &to_append_to) const {
  (void) event;
  to_append_to.append(LOG_EOL);
}

}
