//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/LoggerPatternConverter.h"
namespace s21::parse {

LoggerPatternConverter::LoggerPatternConverter(const std::vector<String>
    &options)
    : PatternConverter(options) {
  name_ = "Logger name";
}

PatternConverter *LoggerPatternConverter::newInstance(const std::vector<String>&
    options) {
  if (options.empty()) {
    static PatternConverter* def = new LoggerPatternConverter(options);
    return def;
  }
  return new LoggerPatternConverter(options);
}

void LoggerPatternConverter::format(const LoggingEvent &event,
                                                String &to_append_to) const {
  to_append_to.append(event.getLoggerName());
}

}