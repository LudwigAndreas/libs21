//
// Created by Ludwig Andreas on 19.07.2023.
//

#include "logger/parse/PatternParser.h"
#include "logger/parse/converters/LiteralPatternConverter.h"

#include <map>

namespace s21::parse {

const Char PatternParser::ESCAPE_CHAR = 0x25; // '%'

bool PatternParser::isUnicodeIdentifier(Char ch) {
  return (ch >= 0x41 && ch <= 0x5A) ||
      (ch >= 0x61 && ch <= 0x7A) ||
      (ch >= 0x30 && ch <= 0x39) ||
      (ch == 0x5F);
}

void PatternParser::parse(const String &pattern,
                          std::vector<std::shared_ptr<PatternConverter> > &converters,
                          std::vector<FormattingInfo> &formatting_infos,
                          const PatternMap &pattern_map) {

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
          if (pattern[i] == ESCAPE_CHAR) {
            current_literal.append(1, c);
            i++;
          } else {
            if (!current_literal.empty()) {
              converters.push_back(LiteralPatternConverter::newInstance
                                       (current_literal));
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

            if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
              formatting_info = FormattingInfo(formatting_info.isLeftAligned(),
                                               (c - 0x30),
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
                           converters,
                           pattern_map);

              state = LITERAL_STATE;
              formatting_info = FormattingInfo::getDefault();

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
          formatting_info = FormattingInfo(
              formatting_info.isLeftAligned(),
              (formatting_info.getMinLength() * 10) + (c - 0x30),
              formatting_info.getMaxLength());

        } else if (c == 0x2E /* '.' */) {
          state = DOT_STATE;

        } else {

          i = finalise(c,
                       pattern,
                       i,
                       current_literal,
                       formatting_info,
                       formatting_infos,
                       converters,
                       pattern_map);
          state = LITERAL_STATE;
          formatting_info = FormattingInfo::getDefault();

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(),
                                  current_literal.end());
          }
        }

        break;

      case DOT_STATE:

        current_literal.append(1, c);

        if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
          formatting_info = FormattingInfo(formatting_info.isLeftAligned(),
                                           formatting_info.getMinLength(),
                                           (c - 0x30));

          state = MAX_STATE;
        } else {
          state = LITERAL_STATE;
        }
        break;

      case MAX_STATE:

        current_literal.append(1, c);

        if ((c >= 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
          formatting_info = FormattingInfo(formatting_info.isLeftAligned(),
                                           formatting_info.getMinLength(),
                                           formatting_info.getMaxLength() *
                                               10 + (c - 0x30));
        } else {

          i = finalise(c,
                       pattern,
                       i,
                       current_literal,
                       formatting_info,
                       formatting_infos,
                       converters,
                       pattern_map);
          state = LITERAL_STATE;
          formatting_info = FormattingInfo::getDefault();

          if (!current_literal.empty()) {
            current_literal.erase(current_literal.begin(),
                                  current_literal.end());
          }
        }
        break;
    } // switch

  } // while

  if (current_literal.length() != 0) {
    converters.push_back(LiteralPatternConverter::newInstance
                             (current_literal));
    formatting_infos.push_back(FormattingInfo::getDefault());
  }
}

size_t PatternParser::extractOptions(const String &pattern,
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
    size_t i, String &conv_buf,
    String &current_literal) {

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

std::shared_ptr<PatternConverter> PatternParser::createConverter(
    const String &converter_id,
    String &current_literal,
    std::vector<String> &options,
    const PatternMap &pattern_map
) {
  String converter_name(converter_id);
  for (size_t i = converter_id.length(); i > 0; i--) {
    converter_name = converter_name.substr(0, i);
    auto iter = pattern_map.find(converter_name);

    if (iter != pattern_map.end()) {
      current_literal.erase(current_literal.begin(),
                            current_literal.end() -
                                (converter_id.length() - 1));
      return ((iter->second)(options));
    }
  }
  return nullptr;
}

size_t PatternParser::finalise(Char c,
                               const String &pattern,
                               size_t i,
                               String &current_literal,
                               const FormattingInfo &formatting_info,
                               std::vector<FormattingInfo> &formatting_infos,
                               std::vector<std::shared_ptr<PatternConverter> > &
                               converters,
                               const PatternMap &pattern_map) {

  String convBuf;
  i = extractConverter(c, pattern, i, convBuf, current_literal);

  if (convBuf.empty()) {
    // Empty conversion specifier
    converters.push_back(LiteralPatternConverter::newInstance
                             (current_literal));
    formatting_infos.push_back(FormattingInfo::getDefault());
  } else {
    String converter_id(convBuf);

    std::vector<String> options;
    i = extractOptions(pattern, i, options);

    std::shared_ptr<PatternConverter> pc(createConverter(converter_id,
                                         current_literal,
                                         options, pattern_map));
    if (pc == nullptr) {
      // Unrecognized conversion specifier
      converters.push_back(LiteralPatternConverter::newInstance
                               (current_literal));
      formatting_infos.push_back(FormattingInfo::getDefault());
    } else {
      converters.push_back(pc);
      formatting_infos.push_back(formatting_info);

      if (current_literal.length() > 0) {
        converters.push_back(LiteralPatternConverter::newInstance
                                 (current_literal));
        formatting_infos.push_back(FormattingInfo::getDefault());
      }
    }
  }
  return i;
}

}