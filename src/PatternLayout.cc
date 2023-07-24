//
// Created by Ludwig Andreas on 25.07.2023.
//

#include "logger/parse/converters/LoggerPatternConverter.h"
#include "logger/parse/converters/ClassNamePatternConverter.h"
#include "logger/parse/converters/ColorEndPatternConverter.h"
#include "logger/parse/converters/ColorStartPatternConverter.h"
#include "logger/parse/converters/DatePatternConverter.h"
#include "logger/parse/converters/ShortFileLocationPatternConverter.h"
#include "logger/parse/converters/FileLocationPatternConverter.h"
#include "logger/parse/converters/FullLocationPatternConverter.h"
#include "logger/parse/converters/LineLocationPatternConverter.h"
#include "logger/parse/converters/MessagePatternConverter.h"
#include "logger/parse/converters/LineSeparatorPatternConverter.h"
#include "logger/parse/converters/MethodLocationPatternConverter.h"
#include "logger/parse/converters/LevelPatternConverter.h"
#include "logger/parse/converters/RelativeTimePatternConverter.h"
#include "logger/parse/converters/ThreadPatternConverter.h"
#include "logger/parse/converters/PropertiesPatternConverter.h"
#include "logger/PatternLayout.h"

#include <utility>

#include "s21.h"

namespace s21::diagnostic {

PatternLayout::PatternLayout() = default;

PatternLayout::PatternLayout(String pattern) :
    conversion_pattern_(std::move(pattern)) {
  activateOptions();
}

PatternLayout::~PatternLayout() {

}

void PatternLayout::setConversionPattern(const String &conversion_pattern) {
  conversion_pattern_ = conversion_pattern;
  activateOptions();
}

String PatternLayout::getConversionPattern() const {
  return conversion_pattern_;
}

void PatternLayout::setOption(const String &option, const String &value) {
  if (s21::to_lower(option) == "fatalcolor") {
    fatal_color_ = value;
  } else if (s21::to_lower(option) == "errorcolor") {
    error_color_ = value;
  } else if (s21::to_lower(option) == "warncolor") {
    warn_color_ = value;
  } else if (s21::to_lower(option) == "infocolor") {
    info_color_ = value;
  } else if (s21::to_lower(option) == "debugcolor") {
    debug_color_ = value;
  } else if (s21::to_lower(option) == "tracecolor") {
    trace_color_ = value;
  }
}

void PatternLayout::activateOptions() {
  String pat = conversion_pattern_;

  if (pat.empty()) {
    pat = String("%m%n");
  }

  pattern_converters_.erase(pattern_converters_.begin(), pattern_converters_
      .end());
  pattern_fields_.erase(pattern_fields_.begin(), pattern_fields_.end());
  parse::PatternParser::parse(pat,
                       pattern_converters_,
                       pattern_fields_,
                       getFormatSpecifiers());
}

void PatternLayout::format(String &output, const parse::LoggingEvent &event) {
  auto formatter_iter = pattern_fields_.begin();

  for (auto converter_iter = pattern_converters_.begin();
       converter_iter != pattern_converters_.end();
       converter_iter++, formatter_iter++) {
    int start_field = (int)output.length();
    (*converter_iter)->format(event, output);
    (*formatter_iter).format(start_field, output);
  }
}

s21::parse::PatternMap PatternLayout::getFormatSpecifiers() {
  s21::parse::PatternMap specs;
//
  specs.insert({"c",
                s21::parse::LoggerPatternConverter::newInstance});
  specs.insert({"logger",
                s21::parse::LoggerPatternConverter::newInstance});
//
  specs.insert({"C",
                s21::parse::ClassNamePatternConverter::newInstance});
  specs.insert({"class",
                s21::parse::ClassNamePatternConverter::newInstance});
//
  specs.insert({"Y",
                s21::parse::ColorStartPatternConverter::newInstance});
  specs.insert({"y",
                s21::parse::ColorEndPatternConverter::newInstance});
//
  specs.insert({"d",
                s21::parse::DatePatternConverter::newInstance});
  specs.insert({"date",
                s21::parse::DatePatternConverter::newInstance});
//
  specs.insert({"f",
                s21::parse::ShortFileLocationPatternConverter::newInstance});
//
  specs.insert({"F",
                s21::parse::FileLocationPatternConverter::newInstance});
  specs.insert({"file",
                s21::parse::FileLocationPatternConverter::newInstance});
//
  specs.insert({"l",
                s21::parse::FullLocationPatternConverter::newInstance});
//
  specs.insert({"L",
                s21::parse::LineLocationPatternConverter::newInstance});
  specs.insert({"line",
                s21::parse::LineLocationPatternConverter::newInstance});
//
  specs.insert({"m",
                s21::parse::MessagePatternConverter::newInstance});
  specs.insert({"message",
                s21::parse::MessagePatternConverter::newInstance});
//
  specs.insert({"n",
                s21::parse::LineSeparatorPatternConverter::newInstance});
//
  specs.insert({"M",
                s21::parse::MethodLocationPatternConverter::newInstance});
  specs.insert({"message",
                s21::parse::MethodLocationPatternConverter::newInstance});
//
  specs.insert({"p",
                s21::parse::LevelPatternConverter::newInstance});
  specs.insert({"level",
                s21::parse::LevelPatternConverter::newInstance});
//
  specs.insert({"r",
                s21::parse::RelativeTimePatternConverter::newInstance});
  specs.insert({"relative",
                s21::parse::RelativeTimePatternConverter::newInstance});
//
  specs.insert({"t",
                s21::parse::ThreadPatternConverter::newInstance});
  specs.insert({"thread",
                s21::parse::ThreadPatternConverter::newInstance});
//
  specs.insert({"X",
                s21::parse::PropertiesPatternConverter::newInstance});
  specs.insert({"properties",
                s21::parse::PropertiesPatternConverter::newInstance});
  return specs;
}

}