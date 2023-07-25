//
// Created by Ludwig Andreas on 22.07.2023.
//

#include "logger/parse/converters/LevelPatternConverter.h"
namespace s21::parse {

LevelPatternConverter::LevelPatternConverter(std::vector<String> &options)
    : PatternConverter(options) {
  name_ = "Level";
}

std::shared_ptr<PatternConverter> LevelPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static std::shared_ptr<PatternConverter> def = std::make_shared<LevelPatternConverter>(options);
    return def;
  }
  return std::make_shared<LevelPatternConverter>(options);
}

void LevelPatternConverter::format(const LoggingEvent &event,
                                   String &to_append_to) const {
  diagnostic::LogLevel level = event.GetLevel();
  switch (level) {
    case diagnostic::LogLevel::Fatal:
      to_append_to.append("FATAL");
      break;
    case diagnostic::LogLevel::Error:
      to_append_to.append("ERROR");
      break;
    case diagnostic::LogLevel::Warn:
      to_append_to.append("WARN");
      break;
    case diagnostic::LogLevel::Info:
      to_append_to.append("INFO");
      break;
    case diagnostic::LogLevel::Debug:
      to_append_to.append("DEBUG");
      break;
    case diagnostic::LogLevel::Trace:
      to_append_to.append("TRACE");
      break;
  }
}

}