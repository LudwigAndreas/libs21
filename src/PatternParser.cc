//
// Created by Ludwig Andreas on 19.07.2023.
//

#include "logger/parser/PatternParser.h"
#include "utils/logger.inc"

#include <map>

const Char s21::parse::PatternParser::ESCAPE_CHAR = 0x25; // '%'

std::vector<String> s21::parse::PatternParser::parse(const String &pattern) {

  std::vector<String> conversion_specifiers;
  std::vector<String> formatting_infos;

  struct formatting_info {};

  String current_literal;
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
              formatting_infos.push_back(String("default"));
              current_literal.erase(current_literal.begin(), current_literal.end());
            }

            current_literal.append(1, c); // append %
            state = CONVERTER_STATE;
//            formatting_info = default_value;
          }
        } else {
          current_literal.append(1, c);
        }
        break;

      case CONVERTER_STATE:

        current_literal.append(1, c);
        switch (c) {
          case 0x2D: // '-'
//            formatting_info = set left align to true
            break;

          case 0x2E: // '.'
            state = DOT_STATE;

            break;

          default:

            if ((c > 0x30 /* '0' */) && c <= 0x39 /* '9' */) {
//              formatting_info = set minLength to (c - 0x30)
              state = MIN_STATE;
            } else {

              conversion_specifiers.push_back(current_literal);
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

          conversion_specifiers.push_back(current_literal);
//            save formatting info
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

          conversion_specifiers.push_back(current_literal);
//            save formatting info
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
    // handle ending
    conversion_specifiers.push_back(current_literal);
//            save formatting info as default
  }
  for (auto &spec : conversion_specifiers) {
    LOG_TRACE("spec \"" << spec << "\"");
  }
  return conversion_specifiers;
}

//size_t PatternParser::extractOptions(const LogString& pattern, LogString::size_type i,
//	std::vector<LogString>& options)
//{
//	while ((i < pattern.length()) && (pattern[i] == 0x7B /* '{' */))
//	{
//		size_t end = pattern.find(0x7D /* '}' */, i);
//
//		if (end == pattern.npos)
//		{
//			break;
//		}
//
//		LogString r(pattern.substr(i + 1, end - i - 1));
//		options.push_back(r);
//		i = end + 1;
//	}
//
//	return i;
//}

//PatternConverterPtr PatternParser::createConverter(
//	const LogString& converterId,
//	LogString& currentLiteral,
//	const PatternMap& rules,
//	std::vector<LogString>& options)
//{
//
//	LogString converterName(converterId);
//
//	for (size_t i = converterId.length(); i > 0; i--)
//	{
//		converterName = converterName.substr(0, i);
//		PatternMap::const_iterator iter = rules.find(converterName);
//
//		if (iter != rules.end())
//		{
//			currentLiteral.erase(currentLiteral.begin(),
//				currentLiteral.end() - (converterId.length() - i));
//			return (iter->second)(options);
//		}
//	}
//
//	LogLog::error(LogString(LOG4CXX_STR("Unrecognized format specifier ")) + converterId);
//
//	return PatternConverterPtr();
//}
//
//size_t PatternParser::finalizeConverter(
//	logchar c, const LogString& pattern, size_t i,
//	LogString& currentLiteral, const FormattingInfoPtr& formattingInfo,
//	const PatternMap&  rules,
//	std::vector<PatternConverterPtr>& patternConverters,
//	std::vector<FormattingInfoPtr>&  formattingInfos)
//{
//	LogString convBuf;
//	i = extractConverter(c, pattern, i, convBuf, currentLiteral);
//
//	if (convBuf.empty())
//	{
//		LogLog::error(LOG4CXX_STR("Empty conversion specifier"));
//		patternConverters.push_back(
//			LiteralPatternConverter::newInstance(currentLiteral));
//		formattingInfos.push_back(FormattingInfo::getDefault());
//	}
//	else
//	{
//		LogString converterId(convBuf);
//
//		std::vector<LogString> options;
//		i = extractOptions(pattern, i, options);
//
//		PatternConverterPtr pc(
//			createConverter(
//				converterId, currentLiteral, rules, options));
//
//		if (pc == NULL)
//		{
//			LogString msg(LOG4CXX_STR("Unrecognized conversion specifier ["));
//			msg.append(converterId);
//			msg.append(LOG4CXX_STR("] in conversion pattern."));
//			LogLog::error(msg);
//			patternConverters.push_back(
//				LiteralPatternConverter::newInstance(currentLiteral));
//			formattingInfos.push_back(FormattingInfo::getDefault());
//		}
//		else
//		{
//			patternConverters.push_back(pc);
//			formattingInfos.push_back(formattingInfo);
//
//			if (currentLiteral.length() > 0)
//			{
//				patternConverters.push_back(
//					LiteralPatternConverter::newInstance(currentLiteral));
//				formattingInfos.push_back(FormattingInfo::getDefault());
//			}
//		}
//	}
//
//	if (!currentLiteral.empty())
//	{
//		currentLiteral.erase(currentLiteral.begin(), currentLiteral.end());
//	}
//
//	return i;
//}