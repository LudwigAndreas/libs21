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

std::shared_ptr<PatternConverter> LoggerPatternConverter::newInstance(const std::vector<String>&
    options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<LoggerPatternConverter>(options);
    return def;
  }
  return std::make_shared<LoggerPatternConverter>(options);
}

void LoggerPatternConverter::format(const LoggingEvent &event,
                                                String &to_append_to) const {
  to_append_to.append(event.getLoggerName());
}

}