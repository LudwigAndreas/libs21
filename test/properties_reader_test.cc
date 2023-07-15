#include "s21.h"

#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <map>

// Fixture
class FileReadingTest : public ::testing::Test {
 protected:
  static void writeTestFile(const std::string& filePath, const std::string& content) {
    std::ofstream outputFile(filePath);
    outputFile << content;
    outputFile.close();
  }
};

TEST_F(FileReadingTest, properties_reader_basic_handler) {
  std::string filePath = "test_file.properties";
  std::string fileContent = "agent.name=cpu_agent_name_linux\n"
                            "agent.type=cpu_agent\n"
                            "agent.update_time_ms=350\n"
                            "agent.metrics=[\"cpu\", \"processes\"]\n"
                            "agent.metrics.cpu.return=double\n"
                            "agent.metrics.cpu.critical_value=\">=20\"\n"
                            "agent.metrics.processes.return=\"double\"\n"
                            "agent.metrics.processes.critical_value=\">=20\"";
  writeTestFile(filePath, fileContent);

  std::map<std::string, std::string> expectedKeyValueMap = {
      {"agent.name", "cpu_agent_name_linux"},
      {"agent.type", "cpu_agent"},
      {"agent.update_time_ms", "350"},
      {"agent.metrics", "[\"cpu\", \"processes\"]"},
      {"agent.metrics.cpu.return", "double"},
      {"agent.metrics.cpu.critical_value", ">=20"},
      {"agent.metrics.processes.return", "double"},
      {"agent.metrics.processes.critical_value", ">=20"}
  };

  std::map<std::string, std::string> actualKeyValueMap = s21::properties_reader(filePath);

  EXPECT_EQ(actualKeyValueMap, expectedKeyValueMap);
}

TEST_F(FileReadingTest, properties_reader_comments_handler) {
  std::string filePath = "test_file.properties";
  std::string fileContent = "agent.name=cpu_agent_name_linux\n"
                            "agent.type=cpu_agent\n"
                            "agent.update_time_ms=350\n"
                            "# agent.comment1=350\n"
                            "agent.metrics=[\"cpu\", \"processes\"]\n"
                            "agent.metrics.cpu.return=double\n"
                            "  # agent.metrics.cpu.comment2=double\n"
                            "agent.metrics.cpu.critical_value=\">=20\"\n"
                            "agent.metrics.processes.return=\"double\"\n"
                            "    #    agent.metrics.cpu.comment3=double\n"
                            "#agent.metrics.cpu.comment=double\n"
                            "agent.metrics.cpu.return=double # comment4\n"
                            "agent.metrics.processes.critical_value=\">=20\"";
  writeTestFile(filePath, fileContent);

  std::map<std::string, std::string> expectedKeyValueMap = {
      {"agent.name", "cpu_agent_name_linux"},
      {"agent.type", "cpu_agent"},
      {"agent.update_time_ms", "350"},
      {"agent.metrics", "[\"cpu\", \"processes\"]"},
      {"agent.metrics.cpu.return", "double"},
      {"agent.metrics.cpu.critical_value", ">=20"},
      {"agent.metrics.processes.return", "double"},
      {"agent.metrics.processes.critical_value", ">=20"}
  };

  std::map<std::string, std::string> actualKeyValueMap = s21::properties_reader(filePath);

  EXPECT_EQ(actualKeyValueMap, expectedKeyValueMap);
}

TEST_F(FileReadingTest, properties_reader_comment_error_handler) {
  std::string filePath = "test_file.properties";
  std::string fileContent = "agent.1=cpu_agent_name_linux\n"
                            "agent.2=cpu_agent\n"
                            "agent.3=350\n"
                            "agent.4#=350\n"
                            "agent.5=#[\"cpu\", \"processes\"]\n"
                            "agent.6.#cpu.return=double\n"
                            "agent.7.cpu.critical_value=\">=20\"\n"
                            "agent.8.processes.return=\"double\"\n"
                            "agent.9.processes.comment=\"double\"#\n"
                            "agent.10.processes.critical_value=\">#=20\"\n"
                            "agent.11=\"\"\n"
                            "=\n";
  writeTestFile(filePath, fileContent);

  std::map<std::string, std::string> expectedKeyValueMap = {
      {"agent.1", "cpu_agent_name_linux"},
      {"agent.2", "cpu_agent"},
      {"agent.3", "350"},
      {"agent.5", ""},
      {"agent.7.cpu.critical_value", ">=20"},
      {"agent.8.processes.return", "double"},
      {"agent.9.processes.comment", "double"},
      {"agent.10.processes.critical_value", ">#=20"},
      {"agent.11", ""}
  };

  std::map<std::string, std::string> actualKeyValueMap = s21::properties_reader(filePath);
  EXPECT_EQ(actualKeyValueMap, expectedKeyValueMap);
}