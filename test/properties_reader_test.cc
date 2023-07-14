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

TEST_F(FileReadingTest, properties_reader) {
  std::string filePath = "test_file.txt";
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
      {"agent.metrics.cpu.critical_value", "\">=20\""},
      {"agent.metrics.processes.return", "\"double\""},
      {"agent.metrics.processes.critical_value", "\">=20\""}
  };

  std::map<std::string, std::string> actualKeyValueMap = s21::properties_reader(filePath);

  EXPECT_EQ(actualKeyValueMap, expectedKeyValueMap);
}

TEST_F(FileReadingTest, properties_reader_comments_handle) {
  std::string filePath = "test_file.txt";
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
      {"agent.metrics.cpu.critical_value", "\">=20\""},
      {"agent.metrics.processes.return", "\"double\""},
      {"agent.metrics.processes.critical_value", "\">=20\""}
  };

  std::map<std::string, std::string> actualKeyValueMap = s21::properties_reader(filePath);

  EXPECT_EQ(actualKeyValueMap, expectedKeyValueMap);
}