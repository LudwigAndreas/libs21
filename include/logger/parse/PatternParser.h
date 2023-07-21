//
// Created by Ludwig Andreas on 19.07.2023.
//

#ifndef S21_SRC_PATTERNPARSER_H_
#define S21_SRC_PATTERNPARSER_H_

#include <vector>
#include <map>

#include "logger/Logger.h"
#include "FormattingInfo.h"
#include "PatternConverter.h"

namespace s21::parse {

class PatternParser {
 private:
  static const Char ESCAPE_CHAR;

  enum {
    LITERAL_STATE = 0,
    CONVERTER_STATE = 1,
    DOT_STATE = 3,
    MIN_STATE = 4,
    MAX_STATE = 5
  };

  PatternParser();

  static bool isUnicodeIdentifier(Char ch);

  static size_t extractConverter(
      Char last_char, const String &pattern,
      size_t i, String& conv_buf,
      String& current_literal);

  static size_t extractOptions(const String pattern,
                               size_t i,
                               std::vector<String> &options);
  static size_t finalise(Char c,
                         const String pattern,
                         size_t i,
                         String &current_literal,
                         const FormattingInfo &formatting_info,
                         std::vector<FormattingInfo>& formatting_infos,
                         std::vector<String> conversion_specifiers);

 public:
  static std::vector<String> parse(const String &pattern);
};
}

#endif //S21_SRC_PATTERNPARSER_H_
