//
// Created by Ludwig Andreas on 22.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSE_CONVERTERS_COLORSTARTPATTERNCONVERTER_H_
#define S21_INCLUDE_LOGGER_PARSE_CONVERTERS_COLORSTARTPATTERNCONVERTER_H_

#include "PatternConverter.h"

namespace s21::parse {
class ColorStartPatternConverter : public PatternConverter {
 private:
  String fatal_color_;
  String error_color_;
  String warn_color_;
  String info_color_;
  String debug_color_;
  String trace_color_;
 public:
  ColorStartPatternConverter();
  ColorStartPatternConverter(std::vector<String> &options);
  static std::shared_ptr<PatternConverter>newInstance(std::vector<String> options);
  void format(const LoggingEvent &event, String &to_append_to) const override;
  void SetFatalColor(const String &fatal_color);
  void SetErrorColor(const String &error_color);
  void SetWarnColor(const String &warn_color);
  void SetInfoColor(const String &info_color);
  void SetDebugColor(const String &debug_color);
  void SetTraceColor(const String &trace_color);

};
}

#endif //S21_INCLUDE_LOGGER_PARSE_CONVERTERS_COLORSTARTPATTERNCONVERTER_H_
