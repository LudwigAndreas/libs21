//
// Created by Ludwig Andreas on 17.07.2023.
//
#include "test.h"

#include <iostream>
#include <utility>
#include <ios>
#include <ostream>
#include <fstream>

#include "../src/logger/Logger.h"
#include "../src/logger/threading/LoggerThreading.h"

class LoggerTest : public ::testing::Test {
 protected:
//  static void initLogger(const std::string& filePath, const std::string& logname) {
//
//  }
};

TEST(LoggerTest, logger_init) {
  s21::diagnostic::Logger<s21::threading::LoggerProcessNoLock> logger(s21::diagnostic::LogLevel::Info, std::string("s21"));

  logger.AddOutputStream(std::cout, false, s21::diagnostic::LogLevel::Error);
  std::fstream fs;
  fs.open("s21.log", std::fstream::in | std::fstream::app);
  logger.AddOutputStream(fs, true, s21::diagnostic::LogLevel::Info);

  WRITELOG(logger, s21::diagnostic::LogLevel::Trace, "Trace")
  WRITELOG(logger, s21::diagnostic::LogLevel::Debug, "Debug")
  WRITELOG(logger, s21::diagnostic::LogLevel::Info, "Info")
  WRITELOG(logger, s21::diagnostic::LogLevel::Warn, "Warn")
  WRITELOG(logger, s21::diagnostic::LogLevel::Error, "Error")
  WRITELOG(logger, s21::diagnostic::LogLevel::Fatal, "Fatal")
}