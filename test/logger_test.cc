//
// Created by Ludwig Andreas on 17.07.2023.
//
#include "test.h"

class LoggerTest : public ::testing::Test {
 protected:
  static void initLogger(const std::string& filePath, const std::string& content) {
    std::ofstream outputFile(filePath);
    outputFile << content;
    outputFile.close();
  }
};