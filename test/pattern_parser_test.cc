#include "test.h"

#include <vector>
#include <map>
#include <fstream>

#include "utils/logger.inc"
#include "logger/parse/PatternParser.h"
#include "logger/parse/LiteralPatternConverter.h"
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

  static std::map<String, s21::parse::PatternConverter *> get_format_specifiers() {
    std::map<String, s21::parse::PatternConverter *> specs;
    specs.insert({"d",
                  s21::parse::LiteralPatternConverter::newInstance("d")});
    specs.insert({"p",
                  s21::parse::LiteralPatternConverter::newInstance("p")});
    return specs;
  }

};

TEST_F(PatternParserTest, parser_debug) {

  std::vector<s21::parse::PatternConverter *> converters;
  std::vector<s21::parse::FormattingInfo> formatting_infos;
  std::map<String, s21::parse::PatternConverter *> pattern_map =
      get_format_specifiers();

  s21::parse::PatternParser::parse("[%d{yyyy-MM-dd HH:mm:ss}] %c %-5.10p - "
                                   "%m%n",
                                   converters,
                                   formatting_infos,
                                   pattern_map);
  EXPECT_EQ(converters.empty(), false);
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

//  auto expect = "[2020-12-24 15:31:46] root INFO  - Hello there!";
//  s21::parse::PatternParser::parse("[%d] %c %-5p - %m%n");
//  auto expect = "[2020-12-24 15:35:39,225] root INFO  - Hello there!";

//  s21::parse::PatternParser::parse("%r %-5p %-20c %m%n");
//  auto expect = "0 INFO  root                 Hello there!";

//  s21::parse::PatternParser::parse("(%F:%C[%M]:%L) %m%n");
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[FooClass]:9) Constructor running";
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[doFoo]:13) Doing foo";
}