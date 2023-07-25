//
// Created by Ludwig Andreas on 22.07.2023.
//

#include <vector>

#include "logger/parse/converters/ColorStartPatternConverter.h"
#include "logger/parse/converters/PatternConverter.h"

namespace s21::parse {

ColorStartPatternConverter::ColorStartPatternConverter() {
  name_ = "Color start";
}

ColorStartPatternConverter::ColorStartPatternConverter(std::vector<String>&
options) :
    PatternConverter(options){
  name_ = "Color start";
}

void ColorStartPatternConverter::SetFatalColor(const String &fatal_color) {
  fatal_color_ = fatal_color;
}
void ColorStartPatternConverter::SetErrorColor(const String &error_color) {
  error_color_ = error_color;
}
void ColorStartPatternConverter::SetWarnColor(const String &warn_color) {
  warn_color_ = warn_color;
}
void ColorStartPatternConverter::SetInfoColor(const String &info_color) {
  info_color_ = info_color;
}
void ColorStartPatternConverter::SetDebugColor(const String &debug_color) {
  debug_color_ = debug_color;
}
void ColorStartPatternConverter::SetTraceColor(const String &trace_color) {
  trace_color_ = trace_color;
}

PatternConverter *ColorStartPatternConverter::newInstance(std::vector<String> options) {
  if (options.empty()) {
    static PatternConverter* def = new ColorStartPatternConverter(options);
    return def;
  }
  return new ColorStartPatternConverter(options);
}

void ColorStartPatternConverter::format(const LoggingEvent &event,
                                        String &to_append_to) const {
  diagnostic::LogLevel log_level = event.GetLevel();
  switch (log_level) {
    case diagnostic::LogLevel::Fatal:
      to_append_to.append(fatal_color_);
      break;
    case diagnostic::LogLevel::Error:
      to_append_to.append(error_color_);
      break;
    case diagnostic::LogLevel::Warn:
      to_append_to.append(warn_color_);
      break;
    case diagnostic::LogLevel::Info:
      to_append_to.append(info_color_);
      break;
    case diagnostic::LogLevel::Debug:
      to_append_to.append(debug_color_);
      break;
    case diagnostic::LogLevel::Trace:
      to_append_to.append(trace_color_);
      break;
  }
}

}