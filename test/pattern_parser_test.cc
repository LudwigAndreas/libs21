#include "test.h"

#include "utils/logger.inc"
#include "logger/parser/PatternParser.h"

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

};

TEST_F(PatternParserTest, patter_init_test) {
//  WRITELOG(logger_, s21::diagnostic::LogLevel::Trace, "test set up");
  s21::parse::PatternParser::parse("[%d{yyyy-MM-dd HH:mm:ss}] %c %-5p - %m%n");
//  auto expect = "[2020-12-24 15:31:46] root INFO  - Hello there!";
//  s21::parse::PatternParser::parse("[%d] %c %-5p - %m%n");
//  auto expect = "[2020-12-24 15:35:39,225] root INFO  - Hello there!";

//  s21::parse::PatternParser::parse("%r %-5p %-20c %m%n");
//  auto expect = "0 INFO  root                 Hello there!";

//  s21::parse::PatternParser::parse("(%F:%C[%M]:%L) %m%n");
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[FooClass]:9) Constructor running";
//  auto expect = "(/home/robert/log4cxx-test-programs/fooclass.cpp:FooClass[doFoo]:13) Doing foo";
}