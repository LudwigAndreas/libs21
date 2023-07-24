//
// Created by Ludwig Andreas on 19.07.2023.
//

#ifndef S21_SRC_PATTERNPARSER_H_
#define S21_SRC_PATTERNPARSER_H_

#include <map>
#include <vector>
#include <functional>


#include "FormattingInfo.h"
#include "logger/parse/converters/PatternConverter.h"

namespace s21::parse {

typedef std::function<PatternConverter*(const std::vector<String>& options)>
    PatternConstructor;
typedef std::map<String, PatternConstructor> PatternMap;

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

  static size_t extractOptions(const String &pattern,
                               size_t i,
                               std::vector<String> &options);

  static size_t finalise(Char c,
                         const String& pattern,
                         size_t i,
                         String &current_literal,
                         const FormattingInfo &formatting_info,
                         std::vector<FormattingInfo>& formatting_infos,
                         std::vector<PatternConverter *>& converters,
                         const PatternMap& pattern_map);

  static PatternConverter* createConverter(
      const String& converter_id,
      String& current_literal,
      std::vector<String>& options,
      const PatternMap& pattern_map
  );

 public:
  static void parse(const String &pattern,
             std::vector<PatternConverter *> &converters,
             std::vector<FormattingInfo> &formatting_infos,
             const PatternMap &pattern_map);
};
}

#endif //S21_SRC_PATTERNPARSER_H_
