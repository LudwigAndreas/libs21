//
// Created by Ludwig Andreas on 19.07.2023.
//

#include "logger/parse/PatternParser.h"
#include "../test/utils/logger.inc"

#include <map>

namespace s21::parse {

const Char PatternParser::ESCAPE_CHAR = 0x25; // '%'

bool PatternParser::isUnicodeIdentifier(Char ch) {
  return (ch >= 0x41 && ch <= 0x5A) ||
      (ch >= 0x61 && ch <= 0x7A) ||
      (ch >= 0x30 && ch <= 0x39) ||
      (ch == 0x5F);
}

std::vector<String> PatternParser::parse(const String &pattern) {

  std::vector<String> conversion_specifiers;
  std::vector<FormattingInfo> formatting_infos;
  std::vector<String> options;

  String current_literal;
  FormattingInfo formatting_info = FormattingInfo::getDefault();
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
              formatting_infos.push_back(FormattingInfo::getDefault());
              current_literal.erase(current_literal.begin(),
                                    current_literal.end());
            }

            current_literal.append(1, c); // append %
            state = CONVERTER_STATE;
            formatting_info = FormattingInfo::getDefault();
          }
        } else {
          current_literal.append(1, c);
        }
        break;

      case CONVERTER_STATE:

        current_literal.append(1, c);
        switch (c) {
          case 0x2D: // '-'
            formatting_info = FormattingInfo(true,
                                             formatting_info.getMinLength(),
                                             formatting_info.getMaxLength()
            );
            break;

          case 0x2E: // '.'
            state = DOT_STATE;

            break;

          default:

            if ((c >= 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//              formatting_info = set minLength to (c - 0x30)
              formatting_info = FormattingInfo(formatting_info.isLeftAligned(),
                                               formatting_info.getMinLength(),
                                               formatting_info.getMaxLength()
              );
              state = MIN_STATE;
            } else {

              i = finalise(c,
                           pattern,
                           i,
                           current_literal,
                           formatting_info,
                           formatting_infos,
                           conversion_specifiers);
//              conversion_specifiers.push_back(current_literal);
//            save formatting info

              state = LITERAL_STATE;
//              formatting_info = set default

              if (!current_literal.empty()) {
                current_literal.erase(current_literal.begin(),
                                      current_literal.end());
              }
            }
        }
        break;

      case MIN_STATE:

        current_literal.append(1, c);

        if ((c >= 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set minLength to (previous-value * 10) + (c - 0x30)

        } else if (c == 0x2E /* '.' */) {
          state = DOT_STATE;

        } else {

          i = finalise(c,
                       pattern,
                       i,
                       current_literal,
                       formatting_info,
                       formatting_infos,
                       conversion_specifiers);;
          state = LITERAL_STATE;
//          formatting_info = default;

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(),
                                  current_literal.end());
          }
        }

        break;

      case DOT_STATE:

        current_literal.append(1, c);

        if ((c >= 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set maxLength to (c - 0x30)
          state = MAX_STATE;
        } else {

          LOG_ERROR(current_literal
                        << " handle error in pattern was expected a digit")

          state = LITERAL_STATE;
        }
        break;

      case MAX_STATE:

        current_literal.append(1, c);

        if ((c >= 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//          formatting_info = set maxLength to ((previous_value * 10) + (c - 0x30))
        } else {

          i = finalise(c,
                       pattern,
                       i,
                       current_literal,
                       formatting_info,
                       formatting_infos,
                       conversion_specifiers);
          state = LITERAL_STATE;
//          formatting_info = default

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(),
                                  current_literal.end());
          }
        }
        break;
    } // switch

  } // while

  if (current_literal.length() != 0) {
    conversion_specifiers.push_back(current_literal);
//            save formatting info as default
  }

//  test
//  for (auto &spec: conversion_specifiers) {
//    LOG_TRACE("spec \"" << spec << "\"");
//  }
//  test
  return conversion_specifiers;
}

size_t PatternParser::extractOptions(const String pattern,
                                     size_t i,
                                     std::vector<String> &options) {
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

size_t PatternParser::extractConverter(
    Char last_char, const String &pattern,
    size_t i, String& conv_buf,
    String& current_literal) {

  if (!conv_buf.empty()) {
    conv_buf.erase(conv_buf.begin(), conv_buf.end());
  }

  conv_buf.append(1, last_char);
  while (i < pattern.length() && isUnicodeIdentifier(pattern[i])) {
    conv_buf.append(1, pattern[i]);
    current_literal.append(1, pattern[i]);
    i++;
  }
  return i;
}

size_t PatternParser::finalise(Char c,
                               const String pattern,
                               size_t i,
                               String &current_literal,
                               const FormattingInfo &formatting_info,
                               std::vector<FormattingInfo>& formatting_infos,
                               std::vector<String> conversion_specifiers) {

  (void) formatting_info;

  String convBuf;
  i = extractConverter(c, pattern, i, convBuf, current_literal);
  LOG_DEBUG(current_literal << " | " << convBuf)

  if (convBuf.empty()) {
    conversion_specifiers.push_back(current_literal);
    formatting_infos.push_back(FormattingInfo::getDefault());
  } else {
    String converter(convBuf);


    std::vector<String> options;
    i = extractOptions(pattern, i, options);
  }
  return i;
}

}