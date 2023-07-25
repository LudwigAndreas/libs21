//
// Created by Ludwig Andreas on 17.07.2023.
//
#include "test.h"

#include <utility>
#include <ios>
#include <ostream>

#include "logger/Logger.h"
#include "logger/LoggerConfigurator.h"

class LoggerTest : public ::testing::Test {
 protected:
//  static void initLogger(const std::string& filePath, const std::string& logname) {
//
//  }
};

TEST(LoggerTest, logger_init) {
  auto logger = s21::diagnostic::Logger::getLogger("MyApp");
  s21::diagnostic::LoggerConfigurator::configure(s21::diagnostic::PatternLayout("%d{%Y-%m-%d %X} %Y%5.5p%y \x1B[35m%-5P%y --- [%M] \x1B[36m%-25.40F%y : %m%n"));

  LOG(logger, s21::diagnostic::LogLevel::Trace, "Some Trace message 1");
  LOG(logger, s21::diagnostic::LogLevel::Debug, "Some Debug message 1");
  LOG(logger, s21::diagnostic::LogLevel::Info, "Some Info message 1");
  LOG(logger, s21::diagnostic::LogLevel::Warn, "Some Warn message 1");
  LOG(logger, s21::diagnostic::LogLevel::Error, "Some Error message 1");
  LOG(logger, s21::diagnostic::LogLevel::Fatal, "Some Fatal message 1");

  LOG_TRACE(logger, "Some Trace message 2");
  LOG_DEBUG(logger, "Some Debug message 2");
  LOG_INFO(logger, "Some Info message 2");
  LOG_WARN(logger, "Some Warn message 2");
  LOG_ERROR(logger, "Some Error message 2");
  LOG_FATAL(logger, "Some Fatal message 2");
}

TEST(LoggerTest, call_to_static_logger) {
  auto logger = s21::diagnostic::Logger::getLogger("MyApp");

  LOG(logger, s21::diagnostic::LogLevel::Trace, "Some Trace message 3");
  LOG(logger, s21::diagnostic::LogLevel::Debug, "Some Debug message 3");
  LOG(logger, s21::diagnostic::LogLevel::Info, "Some Info message 3");
  LOG(logger, s21::diagnostic::LogLevel::Warn, "Some Warn message 3");
  LOG(logger, s21::diagnostic::LogLevel::Error, "Some Error message 3");
  LOG(logger, s21::diagnostic::LogLevel::Fatal, "Some Fatal message 3");

  LOG_TRACE(logger, "Some Trace message 4");
  LOG_DEBUG(logger, "Some Debug message 4");
  LOG_INFO(logger, "Some Info message 4");
  LOG_WARN(logger, "Some Warn message 4");
  LOG_ERROR(logger, "Some Error message 4");
  LOG_FATAL(logger, "Some Fatal message 4");
}

TEST(LoggerTest, new_logger_creation) {
  auto logger = s21::diagnostic::Logger::getLogger("logger");
  logger->SetPatternLayout(s21::diagnostic::PatternLayout("%m%n"));
  logger->AddOutputStream(std::cout, false);

  LOG(logger, s21::diagnostic::LogLevel::Trace, "Some Trace message 5");
  LOG(logger, s21::diagnostic::LogLevel::Debug, "Some Debug message 5");
  LOG(logger, s21::diagnostic::LogLevel::Info, "Some Info message 5");
  LOG(logger, s21::diagnostic::LogLevel::Warn, "Some Warn message 5");
  LOG(logger, s21::diagnostic::LogLevel::Error, "Some Error message 5");
  LOG(logger, s21::diagnostic::LogLevel::Fatal, "Some Fatal message 5");

  LOG_TRACE(logger, "Some Trace message 6");
  LOG_DEBUG(logger, "Some Debug message 6");
  LOG_INFO(logger, "Some Info message 6");
  LOG_WARN(logger, "Some Warn message 6");
  LOG_ERROR(logger, "Some Error message 6");
  LOG_FATAL(logger, "Some Fatal message 6");
}