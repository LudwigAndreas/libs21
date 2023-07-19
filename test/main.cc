#include "test.h"

#include "utils/logger.inc"

int main(int argc, char **argv) {
//  logger = s21::diagnostic::Logger<s21::threading::LoggerProcessNoLock>(s21::diagnostic::LogLevel::Trace, "GoogleTest");
  logger.AddOutputStream(std::cerr, false, s21::diagnostic::LogLevel::Trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}