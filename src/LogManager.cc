//
// Created by Ludwig Andreas on 26.07.2023.
//

#include "logger/LogManager.h"

#include "logger/Logger.h"

namespace s21::diagnostic {

std::map<String, LoggerPtr> LogManager::logger_repo_;
LoggerPtr LogManager::root = nullptr;

LoggerPtr LogManager::getLogger(const String &name) {
  if (!logger_repo_.count(name))
    return std::make_shared<Logger>(name);
  return logger_repo_.at(name);
}

std::map<String, LoggerPtr> LogManager::GetLoggerRepo() {
  return logger_repo_;
}

LoggerPtr LogManager::getRootLogger() {
  return root;
}

}