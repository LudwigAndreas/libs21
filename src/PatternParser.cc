//
// Created by Ludwig Andreas on 19.07.2023.
//

#include "logger/parser/PatternParser.h"
#include "utils/logger.inc"

#include <map>

const Char s21::parse::PatternParser::ESCAPE_CHAR = 0x25; // '%'

size_t s21::parse::PatternParser::extractOptions(const String pattern, size_t i, std::vector<String> &options) {
  while ((i < pattern.length()) && (pattern[i] == 0x7B /* '{' */)) {
    size_t end = pattern.find(0x7D, i);
    if (end == pattern.npos) {
      break;
    }

    String option(pattern.substr(i + 1, end - i - 1));
    options.push_back(option);
    i = end + 1;
  }

  return i;
}

std::vector<String> s21::parse::PatternParser::parse(const String &pattern) {

  std::vector<String> conversion_specifiers;
  std::vector<parser::FormattingInfo> formatting_infos;
  std::vector<String> options;

  String current_literal;
  parser::FormattingInfo formatting_info = parser::FormattingInfo::getDefault();
  size_t pattern_length = pattern.length();
  int state = LITERAL_STATE;
  Char c;
  size_t i = 0;

  while (i < pattern_length) {
    c = pattern[i++];
    switch (state) {

      case LITERAL_STATE:

        if (i == pattern_length) {
          current_literal.append(1, c);
          continue;
        }

        if (c == ESCAPE_CHAR) {
          // peek at the next char
          if (pattern[i] == ESCAPE_CHAR) {
            current_literal.append(1, c);
            i++;
          } else {
            if (!current_literal.empty()) {
              conversion_specifiers.push_back(current_literal);
              formatting_infos.push_back(parser::FormattingInfo::getDefault());
              current_literal.erase(current_literal.begin(), current_literal.end());
            }

            current_literal.append(1, c); // append %
            state = CONVERTER_STATE;
            formatting_info = parser::FormattingInfo::getDefault();
          }
        } else {
          current_literal.append(1, c);
        }
        break;

      case CONVERTER_STATE:

        current_literal.append(1, c);
        switch (c) {
          case 0x2D: // '-'
            formatting_info = parser::FormattingInfo(true,
                                                     formatting_info.getMinLength(),
                                                     formatting_info.getMaxLength()
                                                     );
            break;

          case 0x2E: // '.'
            state = DOT_STATE;

            break;

          default:

            if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//              formatting_info = set minLength to (c - 0x30)
              formatting_info = parser::FormattingInfo(formatting_info.isLeftAligned(),
                                                       formatting_info.getMinLength(),
                                                       formatting_info.getMaxLength()
              );
              state = MIN_STATE;
            } else {

              i = finalizeConverter(c, pattern, i, current_literal, formatting_info,
                                    formatting_infos);
//              conversion_specifiers.push_back(current_literal);
//            save formatting info

              state = LITERAL_STATE;
//              formatting_info = set default

              if (!current_literal.empty()) {
                current_literal.erase(current_literal.begin(), current_literal.end());
              }
            }
        }
        break;

      case MIN_STATE:

        current_literal.append(1, c);

        if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set minLength to (previous-value * 10) + (c - 0x30)

        } else if (c == 0x2E /* '.' */) {
          state = DOT_STATE;

        } else {

          i = finalizeConverter(c, pattern, i, current_literal, formatting_info,
                                formatting_infos);
          state = LITERAL_STATE;
//          formatting_info = default;

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(), current_literal.end());
          }
        }

        break;

      case DOT_STATE:

        current_literal.append(1, c);

        if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set maxLength to (c - 0x30)
          state = MAX_STATE;
        } else {

          LOG_ERROR(current_literal << " handle error in pattern was expected a digit")

          state = LITERAL_STATE;
        }
        break;

      case MAX_STATE:

        current_literal.append(1, c);

        if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set maxLength to ((previous_value * 10) + (c - 0x30))
        } else {

          i = finalizeConverter(c, pattern, i, current_literal, formatting_info,
                                formatting_infos);
          state = LITERAL_STATE;
//          formatting_info = default

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(), current_literal.end());
          }
        }
        break;
    } // switch

  } // while

  if (current_literal.length() != 0) {
    conversion_specifiers.push_back(current_literal);
//            save formatting info as default
  }
  for (auto &spec : conversion_specifiers) {
    LOG_TRACE("spec \"" << spec << "\"");
  }
  return conversion_specifiers;
}

