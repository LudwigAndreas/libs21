//
// Created by Ludwig Andreas on 19.07.2023.
//

#ifndef S21_INCLUDE_LOGGER_PARSER_PATTERNLAYOUT_H_
#define S21_INCLUDE_LOGGER_PARSER_PATTERNLAYOUT_H_

#include "logger/Logger.h"

namespace s21::parse {
class PatternLayout {
 private:

  String conversion_pattern;

  struct test {
    std::func();
    std::vector<String> options;
    s21::parse::FormattingInfo info;
  };

  std::map<String, String> patternConverters;

  std::map<String, String> patternFields;

  String fatal_color_ = "\\x1B[35m";
  String error_color_ = "\\x1B[31m";
  String warn_color_ = "\\x1B[33m";
  String info_color_ = "\\x1B[32m";
  String debug_color_ = "\\x1B[36m";
  String trace_color_ = "\\x1B[34m";

 protected:
  void getFormatSpecs()

 public:
  PatternLayout();

  PatternLayout(const String &pattern);

  ~PatternLayout();

  void setConversionPattern(const String &conversionPattern);

  String getConversionPattern() const;

  void setOption(const LogString &option, const LogString &value);

  void format(String &output);

};
}

#endif //S21_INCLUDE_LOGGER_PARSER_PATTERNLAYOUT_H_
