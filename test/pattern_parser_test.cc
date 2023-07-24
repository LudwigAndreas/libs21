#include "test.h"

#include <vector>
#include <map>
#include <fstream>

#include "utils/logger.inc"
#include "logger/parse/PatternParser.h"
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
#include "logger/parse/FormattingInfo.h"

#include "logger/logger_type.h"

class PatternParserTest : public ::testing::Test {
 protected:

  void SetUp() override {
//    logger_ = initLogger("tests.log", "tests");
//    WRITELOG(logger_, s21::diagnostic::LogLevel::Trace, "Test set up");
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
//    WRITELOG(logger_, s21::diagnostic::LogLevel::Trace, "Test tear down");
  }

  static s21::parse::PatternMap get_format_specifiers() {
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

};

TEST_F(PatternParserTest, basic_pattern_recognision) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  s21::parse::PatternMap pattern_map = get_format_specifiers();
  s21::String pattern = "[%d{yyyy-MM-dd HH:mm:ss}] %c %-5.10p - %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
  EXPECT_EQ(converters.empty(), false);
  EXPECT_EQ(converters.size(), 9);
  EXPECT_EQ(converters.at(0)->getName(), "[");
  EXPECT_EQ(converters.at(0)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(0).isLeftAligned(), false);

  EXPECT_EQ(converters.at(1)->getName(), "Date time");
  EXPECT_EQ(converters.at(1)->getOptions().size(), 1);
  EXPECT_EQ(converters.at(1)->getOptions().at(0), "yyyy-MM-dd HH:mm:ss");
  EXPECT_EQ(formatting_infos.at(1).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(1).isLeftAligned(), false);

  EXPECT_EQ(converters.at(2)->getName(), "] ");
  EXPECT_EQ(converters.at(2)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(2).isLeftAligned(), false);

  EXPECT_EQ(converters.at(3)->getName(), "Logger name");
  EXPECT_EQ(converters.at(3)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(3).isLeftAligned(), false);

  EXPECT_EQ(converters.at(4)->getName(), " ");
  EXPECT_EQ(converters.at(4)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(4).isLeftAligned(), false);

  EXPECT_EQ(converters.at(5)->getName(), "Level");
  EXPECT_EQ(converters.at(5)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMinLength(), 5);
  EXPECT_EQ(formatting_infos.at(5).getMaxLength(), 10);
  EXPECT_EQ(formatting_infos.at(5).isLeftAligned(), true);

  EXPECT_EQ(converters.at(6)->getName(), " - ");
  EXPECT_EQ(converters.at(6)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(6).isLeftAligned(), false);

  EXPECT_EQ(converters.at(7)->getName(), "Message");
  EXPECT_EQ(converters.at(7)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(7).isLeftAligned(), false);

  EXPECT_EQ(converters.at(8)->getName(), "Line separator");
  EXPECT_EQ(converters.at(8)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(8).isLeftAligned(), false);

//  auto expect = "[2020-12-24 15:31:46] root INFO  - Hello there!";
}

TEST_F(PatternParserTest, basic_pattern_recognision_2) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  s21::parse::PatternMap pattern_map =
      get_format_specifiers();
  s21::String pattern = "[%d] %c %-5p - %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
  EXPECT_EQ(converters.empty(), false);
  EXPECT_EQ(converters.size(), 9);

  EXPECT_EQ(converters.at(0)->getName(), "[");
  EXPECT_EQ(converters.at(0)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(0).isLeftAligned(), false);

  EXPECT_EQ(converters.at(1)->getName(), "Date time");
  EXPECT_EQ(converters.at(1)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(1).isLeftAligned(), false);

  EXPECT_EQ(converters.at(2)->getName(), "] ");
  EXPECT_EQ(converters.at(2)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(2).isLeftAligned(), false);

  EXPECT_EQ(converters.at(3)->getName(), "Logger name");
  EXPECT_EQ(converters.at(3)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(3).isLeftAligned(), false);

  EXPECT_EQ(converters.at(4)->getName(), " ");
  EXPECT_EQ(converters.at(4)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(4).isLeftAligned(), false);

  EXPECT_EQ(converters.at(5)->getName(), "Level");
  EXPECT_EQ(converters.at(5)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMinLength(), 5);
  EXPECT_EQ(formatting_infos.at(5).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(5).isLeftAligned(), true);

  EXPECT_EQ(converters.at(6)->getName(), " - ");
  EXPECT_EQ(converters.at(6)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(6).isLeftAligned(), false);

  EXPECT_EQ(converters.at(7)->getName(), "Message");
  EXPECT_EQ(converters.at(7)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(7).isLeftAligned(), false);

  EXPECT_EQ(converters.at(8)->getName(), "Line separator");
  EXPECT_EQ(converters.at(8)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(8).isLeftAligned(), false);
//  auto expect = "[2020-12-24 15:35:39,225] root INFO  - Hello there!";

}

TEST_F(PatternParserTest, basic_pattern_recognision_3) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  s21::parse::PatternMap pattern_map =
      get_format_specifiers();
  s21::String pattern = "%r %-5p %-20c %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
  EXPECT_EQ(converters.empty(), false);
  EXPECT_EQ(converters.size(), 8);

  EXPECT_EQ(converters.at(0)->getName(), "Relative time");
  EXPECT_EQ(converters.at(0)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(0).isLeftAligned(), false);

  EXPECT_EQ(converters.at(1)->getName(), " ");
  EXPECT_EQ(converters.at(1)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(1).isLeftAligned(), false);

  EXPECT_EQ(converters.at(2)->getName(), "Level");
  EXPECT_EQ(converters.at(2)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMinLength(), 5);
  EXPECT_EQ(formatting_infos.at(2).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(2).isLeftAligned(), true);

  EXPECT_EQ(converters.at(3)->getName(), " ");
  EXPECT_EQ(converters.at(3)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(3).isLeftAligned(), false);

  EXPECT_EQ(converters.at(4)->getName(), "Logger name");
  EXPECT_EQ(converters.at(4)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMinLength(), 20);
  EXPECT_EQ(formatting_infos.at(4).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(4).isLeftAligned(), true);

  EXPECT_EQ(converters.at(5)->getName(), " ");
  EXPECT_EQ(converters.at(5)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(5).isLeftAligned(), false);

  EXPECT_EQ(converters.at(6)->getName(), "Message");
  EXPECT_EQ(converters.at(6)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(6).isLeftAligned(), false);

  EXPECT_EQ(converters.at(7)->getName(), "Line separator");
  EXPECT_EQ(converters.at(7)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(7).isLeftAligned(), false);
//  auto expect = "0 INFO  root                 Hello there!";

}

TEST_F(PatternParserTest, basic_pattern_recognision_4) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  s21::parse::PatternMap pattern_map =
      get_format_specifiers();
  s21::String pattern = "(%F:%C[%M]:%L) %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
  EXPECT_EQ(converters.empty(), false);
  EXPECT_EQ(converters.size(), 11);

  EXPECT_EQ(converters.at(0)->getName(), "(");
  EXPECT_EQ(converters.at(0)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(0).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(0).isLeftAligned(), false);

  EXPECT_EQ(converters.at(1)->getName(), "File location");
  EXPECT_EQ(converters.at(1)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(1).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(1).isLeftAligned(), false);

  EXPECT_EQ(converters.at(2)->getName(), ":");
  EXPECT_EQ(converters.at(2)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(2).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(2).isLeftAligned(), false);

  EXPECT_EQ(converters.at(3)->getName(), "Class name");
  EXPECT_EQ(converters.at(3)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(3).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(3).isLeftAligned(), false);

  EXPECT_EQ(converters.at(4)->getName(), "[");
  EXPECT_EQ(converters.at(4)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(4).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(4).isLeftAligned(), false);

  EXPECT_EQ(converters.at(5)->getName(), "Method location");
  EXPECT_EQ(converters.at(5)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(5).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(5).isLeftAligned(), false);

  EXPECT_EQ(converters.at(6)->getName(), "]:");
  EXPECT_EQ(converters.at(6)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(6).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(6).isLeftAligned(), false);

  EXPECT_EQ(converters.at(7)->getName(), "Line");
  EXPECT_EQ(converters.at(7)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(7).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(7).isLeftAligned(), false);

  EXPECT_EQ(converters.at(8)->getName(), ") ");
  EXPECT_EQ(converters.at(8)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(8).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(8).isLeftAligned(), false);

  EXPECT_EQ(converters.at(9)->getName(), "Message");
  EXPECT_EQ(converters.at(9)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(9).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(9).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(9).isLeftAligned(), false);

  EXPECT_EQ(converters.at(10)->getName(), "Line separator");
  EXPECT_EQ(converters.at(10)->getOptions().size(), 0);
  EXPECT_EQ(formatting_infos.at(10).getMinLength(), 0);
  EXPECT_EQ(formatting_infos.at(10).getMaxLength(), INT_MAX);
  EXPECT_EQ(formatting_infos.at(10).isLeftAligned(), false);
//  s21::parse::PatternParser::parse("(%F:%C[%M]:%L) %m%n");
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[FooClass]:9) Constructor running";
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[doFoo]:13) Doing foo";

//  for (size_t i = 0; i < converters.size(); ++i) {
//    LOG_DEBUG("converter: \"" << converters.at(i)->getName() << "\"");
//    for (const auto & j : converters.at(i)->getOptions()) {
//      LOG_DEBUG("   option: " << j);
//    }
//    LOG_DEBUG("   left Align: " << (bool) formatting_infos.at(i)
//        .isLeftAligned());
//    LOG_DEBUG("   min length: " << (int) formatting_infos.at(i)
//        .getMinLength());
//    LOG_DEBUG("   max length: " << (int) formatting_infos.at(i)
//        .getMaxLength());
//  }
}