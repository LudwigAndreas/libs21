#include "test.h"

#include <vector>
#include <map>
#include <fstream>

#include "utils/logger.inc"
#include "logger/parse/PatternParser.h"
#include "logger/parse/converters/LiteralPatternConverter.h"
#include "logger/parse/FormattingInfo.h"

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

  static std::map<String,
                  s21::parse::PatternConverter *> get_format_specifiers() {
    std::map<String, s21::parse::PatternConverter *> specs;
////
//    specs.insert({"c",
//                  s21::parse::LoggerPatternConverter()});
//    specs.insert({"logger",
//                  s21::parse::LoggerPatternConverter()});
////
//    specs.insert({"C",
//                  s21::parse::ClassNamePatternConverter()});
//    specs.insert({"class",
//                  s21::parse::ClassNamePatternConverter()});
////
//    specs.insert({"Y",
//                  s21::parse::ColorStartPatternConverter()});
//    specs.insert({"y",
//                  s21::parse::ColorEndPatternConverter()});
////
//    specs.insert({"d",
//                  s21::parse::DatePatternConverter()});
//    specs.insert({"date",
//                  s21::parse::DatePatternConverter()});
////
//    specs.insert({"f",
//                  s21::parse::ShortFileLocationPatternConverter()});
////
//    specs.insert({"F",
//                  s21::parse::FileLocationPatternConverter()});
//    specs.insert({"file",
//                  s21::parse::FileLocationPatternConverter()});
////
//    specs.insert({"l",
//                  s21::parse::FullLocationPatternConverter()});
////
//    specs.insert({"L",
//                  s21::parse::LineLocationPatternConverter()});
//    specs.insert({"line",
//                  s21::parse::LineLocationPatternConverter()});
////
//    specs.insert({"m",
//                  s21::parse::MessagePatternConverter()});
//    specs.insert({"message",
//                  s21::parse::MessagePatternConverter()});
////
//    specs.insert({"n",
//                  s21::parse::LineSeparatorPatternConverter()});
////
//    specs.insert({"M",
//                  s21::parse::MethodLocationPatternConverter()});
//    specs.insert({"message",
//                  s21::parse::MethodLocationPatternConverter()});
////
//    specs.insert({"p",
//                  s21::parse::LevelPatternConverter()});
//    specs.insert({"level",
//                  s21::parse::LevelPatternConverter()});
////
//    specs.insert({"r",
//                  s21::parse::RelativeTimePatternConverter()});
//    specs.insert({"relative",
//                  s21::parse::RelativeTimePatternConverter()});
////
//    specs.insert({"t",
//                  s21::parse::ThreadPatternConverter()});
//    specs.insert({"thread",
//                  s21::parse::ThreadPatternConverter()});
////
//    specs.insert({"X",
//                  s21::parse::PropertiesPatternConverter()});
//    specs.insert({"properties",
//                  s21::parse::PropertiesPatternConverter()});
    return specs;
  }

};

TEST_F(PatternParserTest, basic_pattern_recognision) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  std::map<String, s21::parse::PatternConverter *> pattern_map =
      get_format_specifiers();
  String pattern = "[%d{yyyy-MM-dd HH:mm:ss}] %c %-5.10p - %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
  EXPECT_EQ(converters.empty(), false);
  EXPECT_EQ(converters.size(), 9);
  EXPECT_EQ(converters.at(0)->getName(), pattern.substr(0, 1));

  EXPECT_EQ(converters.at(1)->getName(), pattern.substr(2, 1));

  EXPECT_EQ(converters.at(2)->getName(), pattern.substr(24, 2));

  EXPECT_EQ(converters.at(3)->getName(), pattern.substr(26, 2));

  EXPECT_EQ(converters.at(4)->getName(), pattern.substr(28, 1));

  EXPECT_EQ(converters.at(5)->getName(), pattern.substr(35, 1));

  EXPECT_EQ(converters.at(6)->getName(), pattern.substr(36, 3));

  EXPECT_EQ(converters.at(7)->getName(), pattern.substr(39, 2));
  EXPECT_EQ(converters.at(8)->getName(), pattern.substr(41, 2));

//  auto expect = "[2020-12-24 15:31:46] root INFO  - Hello there!";
//  s21::parse::PatternParser::parse("[%d] %c %-5p - %m%n");
//  auto expect = "[2020-12-24 15:35:39,225] root INFO  - Hello there!";

//  s21::parse::PatternParser::parse("%r %-5p %-20c %m%n");
//  auto expect = "0 INFO  root                 Hello there!";

//  s21::parse::PatternParser::parse("(%F:%C[%M]:%L) %m%n");
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[FooClass]:9) Constructor running";
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[doFoo]:13) Doing foo";
  for (auto & converter : converters) {
    LOG_DEBUG("converter: \"" << converter->getName() << "\"");
    for (const auto & j : converter->getOptions()) {
      LOG_DEBUG("   option: " << j);
    }
    LOG_DEBUG("   left Align: " << (bool) converter->getFormattingInfo()
        .isLeftAligned());
    LOG_DEBUG("   min length: " << (int) converter->getFormattingInfo()
        .getMinLength());
    LOG_DEBUG("   max length: " << (int) converter->getFormattingInfo()
        .getMaxLength());
  }
}

TEST_F(PatternParserTest, basic_pattern_recognision_2) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  std::map<String, s21::parse::PatternConverter *> pattern_map =
      get_format_specifiers();
  String pattern = "[%d] %c %-5p - %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
//  EXPECT_EQ(converters.empty(), false);
//  EXPECT_EQ(converters.size(), 9);
//  EXPECT_EQ(converters.at(0)->getName(), pattern.substr(0, 1));
//
//  EXPECT_EQ(converters.at(1)->getName(), pattern.substr(2, 1));
//
//  EXPECT_EQ(converters.at(2)->getName(), pattern.substr(24, 2));
//
//  EXPECT_EQ(converters.at(3)->getName(), pattern.substr(26, 2));
//
//  EXPECT_EQ(converters.at(4)->getName(), pattern.substr(28, 1));
//
//  EXPECT_EQ(converters.at(5)->getName(), pattern.substr(35, 1));
//
//  EXPECT_EQ(converters.at(6)->getName(), pattern.substr(36, 3));
//
//  EXPECT_EQ(converters.at(7)->getName(), pattern.substr(39, 2));
//  EXPECT_EQ(converters.at(8)->getName(), pattern.substr(41, 2));
//  auto expect = "[2020-12-24 15:35:39,225] root INFO  - Hello there!";
}

TEST_F(PatternParserTest, basic_pattern_recognision_3) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  std::map<String, s21::parse::PatternConverter *> pattern_map =
      get_format_specifiers();
  String pattern = "%r %-5p %-20c %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
//  EXPECT_EQ(converters.empty(), false);
//  EXPECT_EQ(converters.size(), 9);
//  EXPECT_EQ(converters.at(0)->getName(), pattern.substr(0, 1));
//
//  EXPECT_EQ(converters.at(1)->getName(), pattern.substr(2, 1));
//
//  EXPECT_EQ(converters.at(2)->getName(), pattern.substr(24, 2));
//
//  EXPECT_EQ(converters.at(3)->getName(), pattern.substr(26, 2));
//
//  EXPECT_EQ(converters.at(4)->getName(), pattern.substr(28, 1));
//
//  EXPECT_EQ(converters.at(5)->getName(), pattern.substr(35, 1));
//
//  EXPECT_EQ(converters.at(6)->getName(), pattern.substr(36, 3));
//
//  EXPECT_EQ(converters.at(7)->getName(), pattern.substr(39, 2));
//  EXPECT_EQ(converters.at(8)->getName(), pattern.substr(41, 2));
//  auto expect = "0 INFO  root                 Hello there!";
}

TEST_F(PatternParserTest, basic_pattern_recognision_4) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  std::map<String, s21::parse::PatternConverter *> pattern_map =
      get_format_specifiers();
  String pattern = "(%F:%C[%M]:%L) %m%n";

  s21::parse::PatternParser::parse(
      pattern,
      converters,
      formatting_infos,
      pattern_map);
//  EXPECT_EQ(converters.empty(), false);
//  EXPECT_EQ(converters.size(), 9);
//  EXPECT_EQ(converters.at(0)->getName(), pattern.substr(0, 1));
//
//  EXPECT_EQ(converters.at(1)->getName(), pattern.substr(2, 1));
//
//  EXPECT_EQ(converters.at(2)->getName(), pattern.substr(24, 2));
//
//  EXPECT_EQ(converters.at(3)->getName(), pattern.substr(26, 2));
//
//  EXPECT_EQ(converters.at(4)->getName(), pattern.substr(28, 1));
//
//  EXPECT_EQ(converters.at(5)->getName(), pattern.substr(35, 1));
//
//  EXPECT_EQ(converters.at(6)->getName(), pattern.substr(36, 3));
//
//  EXPECT_EQ(converters.at(7)->getName(), pattern.substr(39, 2));
//  EXPECT_EQ(converters.at(8)->getName(), pattern.substr(41, 2));
//  s21::parse::PatternParser::parse("(%F:%C[%M]:%L) %m%n");
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[FooClass]:9) Constructor running";
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[doFoo]:13) Doing foo";
}