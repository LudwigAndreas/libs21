//
// Created by Ludwig Andreas on 25.07.2023.
//
#include "logger/Logger.h"

namespace s21::diagnostic {

std::map<String, Logger*> Logger::logger_repo_;
Logger* Logger::root;

Logger::Logger(const String& name, LogLevel level,
               const PatternLayout& layout)
    : level_(level), name_(name), pattern_layout_(layout) {
  LoggerInitializer::GetInstance();
  if (!root)
    root = this;
  logger_repo_.insert({name, this});
}


Logger::~Logger() {
  logger_repo_.erase(name_);
}

const String &Logger::GetName() const {
  return name_;
}

Logger *Logger::getLogger(const String &name) {
  if (!logger_repo_.count(name))
    return new Logger(name);
  return logger_repo_.at(name);
}

std::map<String, Logger *> Logger::GetLoggerRepo()  {
  return logger_repo_;
}

Logger *Logger::getRootLogger() {
  return root;
}

void Logger::SetPatternLayout(const PatternLayout &pattern_layout) {
  pattern_layout_ = pattern_layout;
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

void Logger::AddOutputStream(ToStream *os, bool own, LogLevel level)  {
  StreamInfo stream_info(*os, own, level);
  output_streams_.push_back(stream_info);
}

void Logger::ClearOutputStream() {
//    for (auto iter = output_streams_.begin(); iter != output_streams_.end();
//         iter = std::next(iter)) {
//      if (iter->owned)
//        delete iter->p_stream;
//    }
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
