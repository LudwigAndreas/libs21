//
// Created by Ludwig Andreas on 25.07.2023.
//
#include "logger/Logger.h"

#include "logger/LoggerInitializer.h"

namespace s21::diagnostic {

Logger::StreamInfo::StreamInfo(ToStream &p_stream, bool owned, LogLevel level) :
    p_stream(p_stream),
    owned(owned),
    level(level) {}

Logger::Logger(const String &name, LogLevel level,
               PatternLayout &&layout)
    : level_(level), name_(name), pattern_layout_(std::move(layout)) {
  LoggerInitializer::GetInstance();
}

Logger::~Logger() {
  ClearOutputStream();
}

const String &Logger::GetName() const {
  return name_;
}

LoggerPtr Logger::getLogger(const String &name) {
  return LogManager::getLogger(name);
}

std::map<String, LoggerPtr> Logger::GetLoggerRepo() {
  return LogManager::GetLoggerRepo();
}

LoggerPtr Logger::getRootLogger() {
  return LogManager::getRootLogger();
}

void Logger::SetPatternLayout(PatternLayout &&pattern_layout) {
  pattern_layout_ = std::move(pattern_layout);
}

void Logger::AddOutputStream(ToStream &os, bool own, LogLevel level) {
  AddOutputStream(&os, own, level);
}

void Logger::AddOutputStream(ToStream &os, bool own) {
  AddOutputStream(os, own, level_);
}

void Logger::AddOutputStream(ToStream *os, bool own) {
  AddOutputStream(os, own, level_);
}

void Logger::AddOutputStream(ToStream *os, bool own, LogLevel level) {
  StreamInfo stream_info(*os, own, level);
  output_streams_.push_back(stream_info);
}

void Logger::ClearOutputStream() {
  for (auto iter = output_streams_.begin(); iter != output_streams_.end();
       iter = std::next(iter)) {
    if (iter->owned)
      delete &iter->p_stream;
  }
}

void Logger::Log(LogLevel level,
                 String file,
                 int line,
                 String func,
                 String message) {

  String msg;
  pattern_layout_.format(msg,
                         {
                             level,
                             std::move(file),
                             std::move(func),
                             line,
                             name_,
                             std::move(message)
                         }
  );
  threading_protection_.lock();
  for (auto iter = output_streams_.begin(); iter != output_streams_.end();
       iter = std::next(iter)) {
    if (level < iter->level) {
      continue;
    }
    ToStream *p_stream = &iter->p_stream;
    if (!msg.empty()) {
      (*p_stream) << msg;
      p_stream->flush();
    }
  }
  threading_protection_.unlock();
}
}
